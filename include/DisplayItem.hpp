#ifndef DISPLAY_ITEM
#define DISPLAY_ITEM

#include <vector>

#include "Line.hpp"

using namespace std;

namespace matrix_minds
{
  class DisplayItem
  {
  public:
    virtual vector<Line> getMesh() = 0;
  };
}
#endif
