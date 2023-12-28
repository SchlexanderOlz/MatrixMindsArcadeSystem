#include "../include/GraphicsEngine.hpp"


using namespace matrix_minds;

void GraphicsEngine::render(const Shape shape) {
  for (const Line line : shape) {
    render(line);
  }
}

void GraphicsEngine::render(const Line line) {
    const uint x = std::floor((line.getPosX() + 1.0) * ((double)this->getSizeX() / 2.0));
    const uint y = std::floor((line.getPosY() + 1.0) * ((double)this->getSizeY() / 2.0));
    const uint height = std::ceil(line.getHeight() * (double)this->getSizeY());
    const uint width = std::ceil(line.getWidth() * (double)this->getSizeX());
    std::cout << "OX: " << x << " OY: " << y << " Heigt: " << height << " Width: " << width << endl;

    Color template_color = line.getColor();
    Color* color = new Color[height * width]; // Check if the width is necessary
    for (size_t i = 0; i < height * width; ++i) {
      color[i] = template_color; 
    }
    this->off_screen_canvas_->SetPixels(x, y, width, height, color);
    delete[] color;
}
