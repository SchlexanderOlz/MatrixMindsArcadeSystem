#include "GraphicsEngine.hpp"

using namespace matrix_minds;

void GraphicsEngine::render(const vector<const Rectangle *> &shape) {
  for (const Rectangle *line : shape) {
    render(line);
  }
}

void GraphicsEngine::render(const vector<const DisplayItem *> &shape) {
  for (const DisplayItem *item : shape) {
    render(item);
  }
}

// TODO: Implement different font-sizes
void GraphicsEngine::loadDefaultFont(const string &path) {
  if (this->default_font != nullptr)
    return;
  auto tmp = std::make_unique<Font>();
  this->default_font.swap(tmp);
  if (!this->default_font->LoadFont(path.c_str())) {
    throw runtime_error("Foudn not at specified path");
  }
}

void GraphicsEngine::render(const TextField *text) {
  this->loadDefaultFont(DEFAULT_FONT_PATH);
  DrawText(this->off_screen_canvas_, *(this->default_font.get()),
           (int)this->convertToMatrixX(text->getX()),
           (int)this->convertToMatrixY(text->getY()) +
               this->default_font->baseline(),
           text->getColor(), &text->getBGColor(), text->getText().c_str());
}

void GraphicsEngine::render(const Rectangle *line) {
  const uint x = this->convertToMatrixX(line->getPosX());
  const uint y = this->convertToMatrixY(line->getPosY());

  const uint height = std::ceil((line->getHeight() / 2.0) * (double)this->getSizeY());
  const uint width = std::ceil((line->getWidth() / 2.0) * (double)this->getSizeX());

  Color template_color = line->getColor();
  Color *color = new Color[height * width];
  std::fill(color, color + height * width, line->getColor());
  this->off_screen_canvas_->SetPixels(x, y, width, height, color);
  delete[] color;
}

void GraphicsEngine::render(const DisplayItem *item) {
  auto range = item->getRange();
  for (uint x = this->convertToMatrixX(range.first);
       x <= this->convertToMatrixX(range.second); ++x) {
    const auto y_range = item->getRangeAt(
        (static_cast<double>(x) / static_cast<double>(this->getSizeX() / 2.0)) -
        1.0);

    const uint upper =
        this->convertToMatrixY(std::max(y_range.first, y_range.second));
    const uint lower =
        this->convertToMatrixY(std::min(y_range.first, y_range.second));
    const uint height = upper - lower;

    Color *color = new Color[height];
    std::fill(color, color + height, item->getColor());
    this->off_screen_canvas_->SetPixels(x, lower, 1, height, color);
    delete[] color;
  }
}
