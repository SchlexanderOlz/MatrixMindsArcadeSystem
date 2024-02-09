#include "Rectangle.hpp"

std::pair<double, double> Rectangle::getRangeAt(double x) const {
  if (x < this->x || x > this->x + this->width)
    return 0.0;
  return height;
}

void Rectangle::display(shared_ptr<GraphicsEngine> engine) const {
  const uint x = engine->convertToMatrixX(this->getPosX());
  const uint y = engine->convertToMatrixY(this->getPosY());

  const uint height = std::ceil(this->getHeight() * (double)engine->getSizeY());
  const uint width = std::ceil(this->getWidth() * (double)engine->getSizeX());

  Color template_color = this->getColor();
  Color *color = new Color[height * width];
  std::fill(color, color + height * width, this->getColor());
  this->off_screen_canvas_->SetPixels(x, y, width, height, color);
  delete[] color;
}
