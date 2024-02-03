#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <led-matrix.h>
#include <graphics.h>
#include <memory>
#include <iostream>
#include <math.h>

#include "Triangle.hpp"
#include "Rectangle.hpp"

using namespace std;
using namespace rgb_matrix;

namespace matrix_minds {
  class GraphicsEngine {
    private:
      unique_ptr<RGBMatrix> matrix_;
      FrameCanvas* off_screen_canvas_;

      inline uint convertToMatrixX(const double x) const { return std::floor((x + 1.0) * ((double)this->getSizeX() / 2.0)); }
      inline uint convertToMatrixY(const double y) const { return std::floor((y + 1.0) * ((double)this->getSizeY() / 2.0)); }

    public:
      GraphicsEngine(unique_ptr<RGBMatrix> matrix) : matrix_(std::move(matrix)), off_screen_canvas_(this->matrix_->CreateFrameCanvas()) {}
      void render(const vector<Rectangle>& shape);
      void render(const Rectangle& line);
      void render(const Triangle& triangle);
      inline void show() {
        this->off_screen_canvas_ = this->matrix_->SwapOnVSync(this->off_screen_canvas_);
        this->off_screen_canvas_->Clear();
      }
      uint getSizeX() const { return this->matrix_->width() - 1; }
      uint getSizeY() const { return this->matrix_->height() - 1; }
  };
}
#endif
