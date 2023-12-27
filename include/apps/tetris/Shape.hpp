#ifndef SHAPE
#define SHAPE

#include "Coordinate.hpp"
#include "MoveStateIterator.hpp"

namespace tetris {

  /*
   * @brief A accumulation of blocks which are represented by states for which only one
   * state can exist at a time, as a MoveStateIterator
   */
  class Shape {
    private:
      Coordinate coord;
      MoveStateIterator stateIter;
    public:
      Shape(Coordinate coord, MoveStateIterator stateIter) : coord(coord), stateIter(std::move(stateIter)) { }

      void draw() const;
      inline const Coordinate getCoordinate() const { return this->coord; }
      inline void moveDown() { this->coord.y -= 1; }
      inline void moveLeft() { this->coord.x -= 1; }
      inline void moveRight() { this->coord.x += 1; }
      inline void turnRight() { ++this->stateIter; }
      inline void turnLeft() { --this->stateIter; }

      /*
       * @brief Returns the current state as an array. Ownership is moved to the caller
       * @brief array... The owned optional Blocks
       */
      inline array<array<optional<Block>, 4>, 4> intoBlocks() { return std::move((*this->stateIter).intoArray()); }

      /*
       * @brief Returns the current state as an array.
       * @brief array... The owned Blocks as optional pointers
       */
      inline array<array<const Block*, 4>, 4> getBlocks() const {
        return std::move(this->stateIter.current().getBlocks());
      }
  };
}

#endif
