#ifndef MOVESTATE
#define MOVESTATE

#include <vector>
#include <algorithm>
#include <array>
#include <optional>
#include <utility>

#include "Block.hpp"

using namespace std;

namespace tetris {

  /*
   * @brief A specific state in which the Shape can be
   */
  class MoveState {
    private:
      array<array<optional<Block>, 4>, 4> blocks;
    public:
      MoveState(array<pair<Block, Coordinate>, 4> blockPairs);

      /*
       * @brief Returns constant pointers to the blocks of the array
       * @return ...array<Block*>... An owned array of pointers
       */
      const array<array<const Block*, 4>, 4> getBlocks() const;

      /*
       * @brief Moves all blocks of the state to target destination
       * @return ...array<Block?>... A move-constructed block-array
       */
      inline array<array<optional<Block>, 4>, 4> intoArray() { return std::move(this->blocks); }
  };
}

#endif
