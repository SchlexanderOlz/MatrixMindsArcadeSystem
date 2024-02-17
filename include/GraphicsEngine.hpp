#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE

#include <algorithm>
#include <graphics.h>
#include <iostream>
#include <led-matrix.h>
#include <math.h>
#include <memory>

#include "StaticGraphics.hpp"

#define DEFAULT_FONT_PATH "./default.ppm"

using namespace std;
using namespace rgb_matrix;

namespace matrix_minds {
class Rectangle;
class TextField;
class DisplayItem;
/**
 * @brief Rendering Component for displaying of different objects.
 */
class GraphicsEngine {
private:
  unique_ptr<RGBMatrix> matrix_;
  FrameCanvas *off_screen_canvas_;
  unique_ptr<Font> default_font = nullptr;

  /**
   * @brief Maps relative positions in x from -1 to 1.0, to 0 to the current
   * width of the matrix.
   */
  inline uint convertToMatrixX(const double x) const {
    return std::floor((x + 1.0) * ((double)this->getSizeX() / 2.0));
  }
  /**
   * @brief Maps relative positions in y from -1 to 1.0, to 0 to the current
   * width of the matrix.
   */
  inline uint convertToMatrixY(const double y) const {
    return std::floor((y + 1.0) * ((double)this->getSizeY() / 2.0));
  }

public:
  GraphicsEngine(unique_ptr<RGBMatrix> matrix)
      : matrix_(std::move(matrix)),
        off_screen_canvas_(this->matrix_->CreateFrameCanvas()) {}
  /**
   * @brief Loads the default font into memory from the given path. Checks if
   * the font is loaded already and does not perform the operation again if so.
   */
  void loadDefaultFont(const string &path);

  /**
   * @brief Renders a vector of rectangles. Can be used as an optimization as to
   * calling render on the singular object in a loop manually.
   */
  void render(const vector<const Rectangle *> &shape);

  /**
   * @brief Renders a vector of displayable items. Can be used as an
   * optimization as to calling render on the singular object in a loop
   * manually.
   */
  void render(const vector<const DisplayItem *> &shape);

  /**
   * @brief Renders any displayable item. Does this by looping through the
   * x-range of the item and getting the relating y value to this x value. If
   * you are working with rectangles this is less efficient than using the
   * related method for rectanles, cause those can be rendered directly.
   */
  void render(const DisplayItem *item);
  void render(const Rectangle *line);
  void render(const TextField *text);

  /**
   * @brief Displays the current state to the rgb-matrix. Replaces the
   * off-screen canvas with the before-buffer. Clears the new canvas in the
   * process.
   */
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