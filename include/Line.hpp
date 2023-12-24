#ifndef LINE
#define LINE

#include <led-matrix.h>

using namespace rgb_matrix;

namespace matrix_minds {
  class Line {
    private:
      const float x;
      const float y;
      const float height;
      const float width;
      const Color color;

    public:
      Line(float x, float y, float height, float width, Color color) : x(x), y(y), height(height), width(width), color(color) {}
      
      inline float getPosX() const { return this->x; }
      inline float getPosY() const { return this->y; }
      inline float getHeight() const { return this->height; }
      inline float getWidth() const { return this->width; }
      inline Color getColor() const { return this->color; }
  };

  typedef std::vector<Line> Shape;
}


#endif
