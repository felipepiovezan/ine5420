#include "cg/ClippingStrategy.h"

#include <cassert>
#include <iostream>

namespace CG {

bool SimplePointClipping::clipPoint(GPoint& p, const ClippingRect& rect) {
  assert(p.numPoints() == 1);
  auto c = p.coordinates()[0];
  bool onScreen = c.x >= rect.minX && c.x <= rect.maxX &&
                  c.y >= rect.minY && c.y <= rect.maxY;

  if (!onScreen) {
    p.clear();
  }

  return onScreen;
}

bool LBLineClipping::clipLine(GLine& l, const ClippingRect& rect) {
  assert(l.numPoints() == 2);

  auto c1 = l.coordinates()[0];
  auto c2 = l.coordinates()[1];
  auto delta = c2 - c1;

  double u1 = 0.0;
  double u2 = 1.0;
  double p, q, r;

  // Check left, right, bottom and top edges, respectively
  for(int edge = 0; edge < 4; edge++) {
    if      (edge == 0) { p = -delta.x; q = c1.x - rect.minX; }
    else if (edge == 1) { p =  delta.x; q = rect.maxX - c1.x; }
    else if (edge == 2) { p = -delta.y; q = c1.y - rect.minY; }
    else if (edge == 3) { p =  delta.y; q = rect.maxY - c1.y; }

    if (p == 0 && q < 0) {
      // Line parallel to edge and completely outside
      l.clear();
      return false;
    }

    r = q/p;
    if (p < 0) { // line proceeds outside to inside
      if (r > u2) {
        l.clear();
        return false;
      } else if (r > u1) {
        u1 = r;
      }
    } else if (p > 0) { // line proceeds inside to outside
      if (r < u1) {
        l.clear();
        return false;
      } else if (r < u2) {
        u2 = r;
      }
    }
  }

  Coordinate nc1(c1.x + u1 * delta.x, c1.y + u1 * delta.y);
  Coordinate nc2(c1.x + u2 * delta.x, c1.y + u2 * delta.y);
  l = GLine(nc1, nc2);

  return true;
}

/*
 * Implementation as described in http://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
 */
bool SutherlandHodgmanPolygonClipping::clipPolygon(GPolygon& pol, const ClippingRect& rect){
	//pre-allocating output vector
	std::vector<Coordinate> &output = pol.coordinates();
	std::vector<Coordinate> input; input.reserve(output.size());

	//clip against left vertical edge
	{
		output.swap(input);
		output.clear();
		Coordinate S = input.back();
		for(const Coordinate& E : input){
			if(E.x > rect.minX){
				if(S.x < rect.minX){
					//E inside, S outside, calculate the intersection ES x CLipping Edge
					double x = rect.minX;
					double slope = (S.y - E.y) / (S.x - E.x);
					double y = slope * (x - E.x) + E.y;
					output.push_back(Coordinate(x,y));
				}
				output.push_back(E);
			}
			else if (S.x >= rect.minX){
				//E outside, S inside, calculate the intersection ES x CLipping Edge
				double x = rect.minX;
				double slope = (S.y - E.y) / (S.x - E.x);
				double y = slope * (x - E.x) + E.y;
				output.push_back(Coordinate(x,y));
			}
			S = E;
		}
	}
	//clip against top horizontal edge
	{
		output.swap(input);
		output.clear();
		Coordinate S = input.back();
		for(const Coordinate& E : input){
			if(E.y <= rect.maxY){
				if(S.y > rect.maxY){
					//E inside, S outside, calculate the intersection ES x CLipping Edge
					double y = rect.maxY;
					double slopeInverse = (S.x - E.x) / (S.y - E.y);
					double x = slopeInverse * (y - E.y) + E.x;
					output.push_back(Coordinate(x,y));
				}
				output.push_back(E);
			}
			else if (S.y <= rect.maxY){
				//E outside, S inside, calculate the intersection ES x CLipping Edge
				double y = rect.maxY;
				double slopeInverse = (S.x - E.x) / (S.y - E.y);
				double x = slopeInverse * (y - E.y) + E.x;
				output.push_back(Coordinate(x,y));
			}
			S = E;
		}
	}

	//clip against right vertical edge
	{
		output.swap(input);
		output.clear();
		Coordinate S = input.back();
		for(const Coordinate& E : input){
			if(E.x <= rect.maxX){
				if(S.x > rect.maxX){
					//E inside, S outside, calculate the intersection ES x CLipping Edge
					double x = rect.maxX;
					double slope = (S.y - E.y) / (S.x - E.x);
					double y = slope * (x - E.x) + E.y;
					output.push_back(Coordinate(x,y));
				}
				output.push_back(E);
			}
			else if (S.x <= rect.maxX){
				//E outside, S inside, calculate the intersection ES x CLipping Edge
				double x = rect.maxX;
				double slope = (S.y - E.y) / (S.x - E.x);
				double y = slope * (x - E.x) + E.y;
				output.push_back(Coordinate(x,y));
			}
			S = E;
		}
	}

	//clip against bottom horizontal edge
	{
		output.swap(input);
		output.clear();
		Coordinate S = input.back();
		for(const Coordinate& E : input){
			if(E.y >= rect.minY){
				if(S.y < rect.minY){
					//E inside, S outside, calculate the intersection ES x CLipping Edge
					double y = rect.minY;
					double slopeInverse = (S.x - E.x) / (S.y - E.y);
					double x = slopeInverse * (y - E.y) + E.x;
					output.push_back(Coordinate(x,y));
				}
				output.push_back(E);
			}
			else if (S.y >= rect.minY){
				//E outside, S inside, calculate the intersection ES x CLipping Edge
				double y = rect.minY;
				double slopeInverse = (S.x - E.x) / (S.y - E.y);
				double x = slopeInverse * (y - E.y) + E.x;
				output.push_back(Coordinate(x,y));
			}
			S = E;
		}
	}

	if(pol.numPoints() > 0)
		return true;
	else
		return false;
}

bool CurveClipping::clipCurve(Curve& curve, const ClippingRect& rect) {
  const auto &originalPath = curve.getPath();
  std::vector<Coordinate> newPath;
  newPath.reserve(originalPath.size());
  LBLineClipping lineClipper;
  SutherlandHodgmanPolygonClipping polygonClipper;

  Coordinate prevCoord;  // the previous coordinate
  bool prevInside = true; // whether the previous coordinate was inside the clippingRect or not
  std::vector<Coordinate> outsideCoords; // Used to detect curves that go outside a border and come from another border

  for(auto &c : originalPath) {
    if (c.x >= rect.minX && c.x <= rect.maxX &&
        c.y >= rect.minY && c.y <= rect.maxY)  // Coordinate inside
    {
      if (!prevInside) { // Previous coordinate outside, current inside
        outsideCoords.push_back(c);
        GPolygon polygonToClip(outsideCoords);
        polygonClipper.clipPolygon(polygonToClip, rect);
        const auto &clippedCoords = polygonToClip.coordinates();

        newPath.insert(newPath.end(), clippedCoords.begin(), clippedCoords.end());
      } else {
        newPath.push_back(c);
      }

      outsideCoords.clear();
      prevInside = true;
    }
    else // Coordinate outside
    {
      if (prevInside && newPath.size() != 0) { // Previous coordinate inside, current outside
        GLine lineToClip(prevCoord, c);
        lineClipper.clipLine(lineToClip, rect);
        auto clippedCoords = lineToClip.coordinates();
        newPath.push_back(clippedCoords[1]); // add just the new coordinate, last one already inserted
      }

      outsideCoords.push_back(c);
      prevInside = false;
    }
    prevCoord = c;
  }

  curve.setPath(newPath);
  return !newPath.empty();
}

}
