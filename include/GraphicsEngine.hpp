#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <algorithm>
#include <graphics.h>
#include <iostream>
#include <led-matrix.h>
#include <math.h>
#include <memory>

#include "DisplayItem.hpp"
#include "Rectangle.hpp"
#include "StaticGraphics.hpp"
#include "Triangle.hpp"

#define DEFAULT_FONT_PATH "./default.ppm"

using namespace std;
using namespace rgb_matrix;

namespace matrix_minds {
class GraphicsEngine {
private:
  unique_ptr<RGBMatrix> matrix_;
  FrameCanvas *off_screen_canvas_;
  unique_ptr<Font> default_font = nullptr;

  inline uint convertToMatrixX(const double x) const {
    return std::floor((x + 1.0) * ((double)this->getSizeX() / 2.0));
  }
  inline uint convertToMatrixY(const double y) const {
    return std::floor((y + 1.0) * ((double)this->getSizeY() / 2.0));
  }

public:
  GraphicsEngine(unique_ptr<RGBMatrix> matrix)
      : matrix_(std::move(matrix)),
        off_screen_canvas_(this->matrix_->CreateFrameCanvas()) {}
  void loadDefaultFont(const string &path);
  void render(const vector<const Rectangle *> &shape);
  void render(const vector<const DisplayItem *> &shape);
  void render(const DisplayItem *item);
  void render(const Rectangle *line);
  void render(const TextField *text);
  inline void show() {
    this->off_screen_canvas_ =
        this->matrix_->SwapOnVSync(this->off_screen_canvas_);
    this->off_screen_canvas_->Clear();
  }
  uint getSizeX() const { return this->matrix_->width() - 1; }
  uint getSizeY() const { return this->matrix_->height() - 1; }
};
} // namespace matrix_minds
#endif
