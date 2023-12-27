#include <iostream>

#ifndef COORD 
#define COORD 

namespace tetris {
  struct Coordinate {
    size_t x;
    size_t y;
    Coordinate(size_t x, size_t y) : x(x), y(y) {}
    Coordinate() {}

    bool operator ==(Coordinate other) const {
      return this->x == other.x && this->y == other.y;
    }
  };
}
#endif
