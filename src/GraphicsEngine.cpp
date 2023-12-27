#include "../include/GraphicsEngine.hpp"


using namespace matrix_minds;

void GraphicsEngine::render(const Shape shape) {
  for (const Line line : shape) {
    render(line);
  }
}

void GraphicsEngine::render(const Line line) {
    const uint x = (line.getPosX() + 1.0) * (float)this->getSizeX() - (float)this->getSizeX();
    const uint y = (line.getPosY() + 1.0) * (float)this->getSizeY() - (float)this->getSizeY();
    const uint height = std::ceil(line.getHeight() * (float)this->getSizeY());
    const uint width = std::ceil(line.getWidth() * (float)this->getSizeX());
    std::cout << "OX: " << x << " OY: " << y << " Heigt: " << height << " Width: " << width << endl;

    Color template_color = line.getColor();
    Color* color = new Color[height * width]; // Check if the width is necessary
    for (size_t i = 0; i <= height * width; ++i) {
      color[i] = template_color; 
    }

    this->off_screen_canvas_->SetPixels(x, y, width, height, color);
}
