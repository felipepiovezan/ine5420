#ifndef DECORATIONS_H_
#define DECORATIONS_H_

namespace CG {

class Color {
 public:
  Color() : r(0), g(0), b(0), a(1) {}
  Color(double r, double g, double b, double a = 1) : r(r), g(g), b(b), a(a) {}
  double r, g, b, a;
};

/**
 * Specifies drawing configurations, like line color, line width, filling color etc
 */
class Decoration {
 public:
  Decoration() : fillColor(0, 0, 0, 0) {}  // alpha fill by default

  const Color getFillColor() const { return fillColor; }
  const Color getLineColor() const { return lineColor; }
  const double getLineWidth() const { return lineWidth; }

  void setFillColor(const Color& color) { this->fillColor = color; }
  void setLineColor(const Color& color) { this->lineColor = color; }
  void setLineWidth(double width) { this->lineWidth = width; }

 protected:
  Color fillColor;
  Color lineColor;
  double lineWidth = 1.0;
};

}  // namespace CG

#endif
