#ifndef LINE
#define LINE

#include <led-matrix.h>

using namespace rgb_matrix;

namespace matrix_minds
{
  class Line
  {
  private:
    const double x;
    const double y;
    const double height;
    const double width;
    const Color color;

  public:
    Line(double x, double y, double height, double width, Color color) : x(x), y(y), height(height), width(width), color(color) {}

    inline double getPosX() const { return this->x; }
    inline double getPosY() const { return this->y; }
    inline double getHeight() const { return this->height; }
    inline double getWidth() const { return this->width; }
    inline Color getColor() const { return this->color; }
  };

  typedef std::vector<Line> Shape;
}

#endif
