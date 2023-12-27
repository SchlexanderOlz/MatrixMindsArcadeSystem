#include "apps/tetris/MoveState.hpp"

using namespace tetris;

MoveState::MoveState(array<pair<Block, Coordinate>, 4> blockPairs) {
  for (auto &block : blockPairs) {
    Coordinate coord = block.second;
    this->blocks[coord.y][coord.x] = std::move(block.first);
  }
}

const array<array<const Block *, 4>, 4> MoveState::getBlocks() const {
  static array<array<const Block *, 4>, 4> blockPointers;

  for (size_t y = 0; y < 4; ++y) {
    for (size_t x = 0; x < 4; ++x) {
      const auto& block = this->blocks[y][x];
      if (!block.has_value()) {
        blockPointers[y][x] = nullptr;
        continue;
      }
      blockPointers[y][x] = &block.value();
    }
  }

  return std::move(blockPointers);
};
