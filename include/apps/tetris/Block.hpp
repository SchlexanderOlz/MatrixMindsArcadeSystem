#ifndef BLOCK 
#define BLOCK 

#include "Color.hpp"
#include "Coordinate.hpp"


namespace tetris {
  class Block {
    private:
      Color color;
    public:
      Block() { this->color = Color::RED; };
      Block(Color color) : color(color) {};
      inline void setColor(Color color) { this->color = color; }
      inline Color getColor() const { return this->color; }
  };
}
#endif
