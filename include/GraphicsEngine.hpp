#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <led-matrix.h>
#include <graphics.h>
#include <memory>
#include <iostream>
#include <math.h>

#include "DisplayItem.hpp"

using namespace rgb_matrix;

namespace matrix_minds {
  class GraphicsEngine {
    private:
      unique_ptr<RGBMatrix> matrix_;
      FrameCanvas* off_screen_canvas_;

    public:
      GraphicsEngine(unique_ptr<RGBMatrix> matrix) : matrix_(std::move(matrix)), off_screen_canvas_(this->matrix_->CreateFrameCanvas()) {}
      void render(const Shape shape);
      void render(const Line line);
      inline void show() {
        this->off_screen_canvas_ = this->matrix_->SwapOnVSync(this->off_screen_canvas_);
        this->off_screen_canvas_ = this->matrix_->CreateFrameCanvas();
      }
      uint getSizeX() const { return this->matrix_->width() - 1; }
      uint getSizeY() const { return this->matrix_->height() - 1; }
  };
}
#endif
