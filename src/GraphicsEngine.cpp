#include "../include/GraphicsEngine.hpp"


using namespace matrix_minds;

void GraphicsEngine::render(const Shape& shape) {
  // This is a problem
}

void GraphicsEngine::render(const PositionalObject& point) {
    const uint x = this->convertToX(&point);
    const uint y = this->convertToY(&point);

    const Color color = point.getColor();
    this->off_screen_canvas_->SetPixel(x, y, color.r, color.g, color.b);
}

void GraphicsEngine::render(const RectangularArea& line) {
    const uint x = this->convertToX(&line);
    const uint y = this->convertToY(&line);
    const uint height = std::ceil(line.getHeight() * (double)this->getSizeY());
    const uint width = std::ceil(line.getWidth() * (double)this->getSizeX());

    Color template_color = line.getColor();
    Color* color = new Color[height * width]; // Check if the width is necessary
    for (size_t i = 0; i < height * width; ++i) {
      color[i] = template_color; 
    }
    this->off_screen_canvas_->SetPixels(x, y, width, height, color);
    delete[] color;
}
