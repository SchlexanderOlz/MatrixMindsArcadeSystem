#include "../include/GraphicsEngine.hpp"


using namespace matrix_minds;

void GraphicsEngine::render(const shared_ptr<DisplayItem> display_item) {
  const Shape mesh = display_item->getMesh();

  for (const Line line : mesh) {
    const uint x = (line.getPosX() + 1.0) * this->getSizeX() - this->getSizeX();
    const uint y = (line.getPosY() + 1.0) * this->getSizeY() - this->getSizeY();
    const uint height = line.getHeight() * this->getSizeY();
    const uint width = line.getWidth() * this->getSizeX();

    Color template_color = line.getColor();
    Color* color = new Color[height * width]; // Check if the width is necessary
    for (size_t i = 0; i < height * width; ++i) {
      color[i] = template_color; 
    }

    off_screen_canvas_->SetPixels(x, y, width, height, color);
  }
}

