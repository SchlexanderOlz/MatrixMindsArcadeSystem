#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <led-matrix.h>
#include <graphics.h>
#include <memory>

#include "DisplayItem.hpp"

using namespace rgb_matrix;

namespace matrix_minds {
  class GraphicsEngine {
    private:
      const unique_ptr<RGBMatrix> matrix_;
      unique_ptr<FrameCanvas> off_screen_canvas_;

    public:
      GraphicsEngine(unique_ptr<RGBMatrix> matrix) : matrix_(std::move(matrix)), off_screen_canvas_(matrix->CreateFrameCanvas()) {}
      void render(const Shape shape);
      void render(const Line line);
      inline void show() {
        this->matrix_->SwapOnVSync(this->off_screen_canvas_.get());
        auto tmp = unique_ptr<FrameCanvas>(matrix_->CreateFrameCanvas());
        this->off_screen_canvas_.swap(tmp);
      }
      uint getSizeX() const { return this->matrix_->width() - 1; }
      uint getSizeY() const { return this->matrix_->height() - 1; }
  };
}
#endif
