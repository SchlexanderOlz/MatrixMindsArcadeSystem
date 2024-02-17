#include "Rectangle.hpp"


using namespace matrix_minds;

std::pair<double, double> Rectangle::getRangeAt(double x) const {
  if (x < this->x || x > this->x + this->width)
    return std::make_pair(0.0, 0.0);
  return std::make_pair(this->y, this->y + height);
}

void Rectangle::display(shared_ptr<GraphicsEngine> engine) const {
    engine->render(this);
}

