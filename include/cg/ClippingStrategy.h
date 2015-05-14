#ifndef INCLUDE_CG_CLIPPINGSTRATEGY_H_
#define INCLUDE_CG_CLIPPINGSTRATEGY_H_

#include "cg/objects.h"

namespace CG {

typedef struct {
  double minX, maxX, minY, maxY;
}
ClippingRect;

template <typename PointStrategy, typename LineStrategy, typename PolygonStrategy, typename CurveStrategy>
class ClippingStrategy : private PointStrategy, private LineStrategy, private PolygonStrategy, private CurveStrategy {
  using PointStrategy::clipPoint;
  using LineStrategy::clipLine;
  using PolygonStrategy::clipPolygon;
  using CurveStrategy::clipCurve;

public:
  bool clip(GPoint& p, const ClippingRect& rect) {
    return clipPoint(p, rect);
  }
  bool clip(GLine& l, const ClippingRect& rect) {
    return clipLine(l, rect);
  }
  bool clip(GPolygon& pol, const ClippingRect& rect) {
    return clipPolygon(pol, rect);
  }
  bool clip(Curve& curve, const ClippingRect& rect) {
    return clipCurve(curve, rect);
  }
  bool clip(G3dObject& obj, const ClippingRect& rect){
	  obj._actualFaces.clear();
	  bool clip = false;
	  for(const auto& face : obj.faceList()){
		  CG::GPolygon pol;
      bool addFace = true;
		  for(int index : face) {
        // Do not add the face if some of its coordinates is partially behind camera
        if (obj._coordinates[index].z <= 0) {
          addFace = false;
        }

			  pol.addCoordinate(obj._coordinates[index]);
      }

		  if(clipPolygon(pol, rect) && addFace){
			  obj._actualFaces.push_back(std::move(pol));
			  clip = true;
		  }
	  }
	  return clip;
  }
};

class SimplePointClipping {
public:
  bool clipPoint(GPoint& p, const ClippingRect& rect);
};

class LBLineClipping {
public:
  bool clipLine(GLine& l, const ClippingRect& rect);
};

class NLNLineClipping {
public:
  bool clipLine(GLine& l, const ClippingRect& rect);
private:
  inline void leftcolumn(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
  inline void centrecolumn(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
  inline void topleftcorner(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
  inline void leftedge(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
  inline void leftbottomregion(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&, const double &,const double &,const double &);
  inline void p2bottom(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
  inline void inside(const double &,const double &,const double &,const double &,double &,double &,double &,double &, bool&);
  inline void p2left(const double &,const double &,const double &,const double &,double &,double &,double &,double &);
  inline void p2lefttop(const double &,const double &,const double &,const double &,double &,double &,double &,double &);
};

class SutherlandHodgmanPolygonClipping {
public:
  bool clipPolygon(GPolygon& pol, const ClippingRect& rect);
};

class CurveClipping {
public:
  bool clipCurve(Curve& curve, const ClippingRect& rect);
};

}



#endif /* INCLUDE_CG_CLIPPINGSTRATEGY_H_ */
