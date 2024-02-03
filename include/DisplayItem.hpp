#ifndef DISPLAY_ITEM
#define DISPLAY_ITEM

#include <vector>

#include "Rectangle.hpp"

using namespace std;

namespace matrix_minds {
  class DisplayItem {
    public:
      virtual vector<Rectangle> getMesh() = 0;
  };
}
#endif
