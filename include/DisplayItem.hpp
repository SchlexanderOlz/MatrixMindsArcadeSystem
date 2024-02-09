#ifndef DISPLAY_ITEM
#define DISPLAY_ITEM

#include <vector>

#include "GraphicsEngine.hpp"
#include "Rectangle.hpp"

using namespace std;

namespace matrix_minds {
class DisplayItem {
private:
  const Color color_;

public:
  DisplayItem(Color color) : color_(std::move(color)) {}

  virtual std::pair<double, double> getRange() const = 0;
  virtual std::pair<double, double> getRangeAt(double x) const = 0;
  inline virtual void display(shared_ptr<GraphicsEngine> engine) const {
    engine->render(this);
  }
  virtual inline Color getColor() const { return this->color_; }
};
} // namespace matrix_minds
#endif
