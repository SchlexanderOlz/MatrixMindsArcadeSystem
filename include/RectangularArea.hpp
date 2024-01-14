#ifndef AREA 
#define AREA 

#include <led-matrix.h>
#include "PositionalObject.hpp"

using namespace rgb_matrix;

namespace matrix_minds
{
  class RectangularArea : public PositionalObject 
  {
  private:
    const double height;
    const double width;

  public:
    RectangularArea(double x, double y, double height, double width, Color color) : PositionalObject(x, y, color), height(height), width(width) {}

    inline double getHeight() const { return this->height; }
    inline double getWidth() const { return this->width; }
  };

}

#endif
