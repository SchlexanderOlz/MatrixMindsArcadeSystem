#ifndef POINT 
#define POINT 

#include <led-matrix.h>

using namespace rgb_matrix;

namespace matrix_minds
{
/**
 * @brief A point is just an area which has a height and width of zero but always at least one pixel
*/
  class PositionalObject 
  {
  private:
    const double x;
    const double y;
    const Color color;

  public:
    PositionalObject(double x, double y, Color color) : x(x), y(y), color(color) {}

    virtual inline double getPosX() const { return this->x; }
    virtual inline double getPosY() const { return this->y; }
    inline Color getColor() const { return this->color; }
  };


  typedef std::vector<PositionalObject> Shape;
}

#endif
