#ifndef DISPLAY_ITEM
#define DISPLAY_ITEM

#include <vector>

#include "RectangularArea.hpp"

using namespace std;

namespace matrix_minds
{
  class DisplayItem
  {
  public:
    virtual vector<RectangularArea> getMesh() = 0;
  };
}
#endif
