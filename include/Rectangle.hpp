#ifndef LINE
#define LINE

#include <led-matrix.h>

#include "DisplayItem.hpp"

using namespace rgb_matrix;

namespace matrix_minds {
class Rectangle : public DisplayItem {
private:
  const double x;
  const double y;
  const double height;
  const double width;

public:
  Rectangle(double x, double y, double height, double width, Color color)
      : x(x), y(y), height(height), width(width),
        DisplayItem(std::move(color)) {}

  inline double getPosX() const { return this->x; }
  inline double getPosY() const { return this->y; }
  inline double getHeight() const { return this->height; }
  inline double getWidth() const { return this->width; }

  std::pair<double, double> getRangeAt(double x) const override;
  inline std::pair<double, double> getRange() const override {
    return std::make_pair(this->x, this->x + width);
  }
  inline void display(shared_ptr<GraphicsEngine> engine) const override {
    engine->render(this);
  }
};
}; // namespace matrix_minds

#endif
