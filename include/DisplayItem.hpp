#include "GraphicsEngine.hpp"
#ifndef DISPLAY_ITEM
#define DISPLAY_ITEM

#include <vector>
#include <memory>
#include <led-matrix.h>


using namespace std;

namespace matrix_minds {
class GraphicsEngine;
class DisplayItem {
protected:
  const rgb_matrix::Color color_;

public:
  DisplayItem(rgb_matrix::Color color) : color_(std::move(color)) {}

  virtual std::pair<double, double> getRange() const = 0;
  virtual std::pair<double, double> getRangeAt(double x) const = 0;
  virtual void display(shared_ptr<GraphicsEngine> engine) const;
  inline virtual rgb_matrix::Color getColor() const { return this->color_; }

  virtual ~DisplayItem() = default;
};
} // namespace matrix_minds
#endif