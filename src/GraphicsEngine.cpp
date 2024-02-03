#include "../include/GraphicsEngine.hpp"


using namespace matrix_minds;

void GraphicsEngine::render(const vector<Rectangle>& shape) {
  for (const Rectangle& line : shape) {
    render(line);
  }
}

void GraphicsEngine::render(const Rectangle& line) {
    const uint x = this->convertToMatrixX(line.getPosX());
    const uint y = this->convertToMatrixY(line.getPosY());

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

void GraphicsEngine::render(const Triangle& triangle) {
  auto range = triangle.getRange();
  for (size_t x = range.first; x < range.second; ++x) {
    auto y_range = triangle.getRangeAt(x);
 
    const uint upper = this->convertToMatrixY(std::max(y_range.first, y_range.second));
    const uint lower = this->convertToMatrixX(std::min(y_range.first, y_range.second));
    const uint height = upper - lower;

    Color* color = new Color[height]; 
    for (size_t i = 0; i < height; ++i) {
      color[i] = triangle.getColor();
    }
    this->off_screen_canvas_->SetPixels(x, lower, 1, height, color);
    delete[] color;
  }
}