#include "static-graphics/Fields.hpp"

using namespace matrix_minds;

void TextField::apply(shared_ptr<GraphicsEngine> engine) const {
  engine->render(this);
}

void Box::apply(shared_ptr<GraphicsEngine> engine) const {
  const double pxx1 = 1.0 / engine->getSizeX();
  const double pxy1 = 1.0 / engine->getSizeY();

  Rectangle line_1(this->x - (this->width / 2.0),
                   this->y - (this->height / 2.0), this->height, pxx1,
                   this->color);
  Rectangle line_2(this->x + (this->width / 2.0),
                   this->y - (this->height / 2.0), this->height, pxx1,
                   this->color);
  Rectangle line_3(this->x - (this->width / 2.0),
                   this->y - (this->height / 2.0), pxy1, this->width,
                   this->color);
  Rectangle line_4(this->x - (this->width / 2.0),
                   this->y + (this->height / 2.0), pxy1, this->width,
                   this->color);

  engine->render(&line_1);
  engine->render(&line_2);
  engine->render(&line_3);
  engine->render(&line_4);
}
