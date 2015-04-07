#ifndef DECORATIONS_H_
#define DECORATIONS_H_

namespace CG {

class Color {
 public:
  Color() : r(0), g(0), b(0) {}
  Color(double r, double g, double b) : r(r), g(g), b(b) {}
  double r, g, b;
};

/**
 * Specifies drawing configurations, like line color, line width, filling color etc
 */
class Decoration {
 public:
  const Color getLineColor() const { return lineColor; }
  const double getLineWidth() const { return lineWidth; }
  const bool isFilled() const { return filled; }
  const Color getFillColor() const { return fillColor; }

  void setLineColor(const Color& color) { this->lineColor = color; }
  void setLineWidth(double width) { this->lineWidth = width; }
  void setFilled(bool filled = true) { this->filled = filled; }
  void setFillColor(const Color& color) { this->fillColor = color; }

 protected:
  Color lineColor;
  double lineWidth = 1.0;
  bool filled = false;
  Color fillColor;
};

}  // namespace CG

#endif
