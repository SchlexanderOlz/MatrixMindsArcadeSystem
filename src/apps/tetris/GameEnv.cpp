#include "apps/tetris/GameEnv.hpp"

using namespace tetris;

void GameEnv::moveShapeDown() {
  if (!this->canMoveShape(0, -1)) {
    throw CantMoveException();
  }
  this->score += 1;
  this->shape.moveDown();
}

void GameEnv::moveShapeLeft() {
  if (!this->canMoveShape(-1, 0)) {
    throw CantMoveException();
  }
  this->score += 1;
  this->shape.moveLeft();
}

void GameEnv::moveShapeRight() {
  if (!this->canMoveShape(1, 0)) {
    throw CantMoveException();
  }
  this->score += 1;
  this->shape.moveRight();
}

void GameEnv::turnShapeLeft() {
  this->shape.turnLeft();
  if (!this->canMoveShape(0, 0)) {
    this->shape.turnRight();
    throw CantMoveException();
  }
}

void GameEnv::turnShapeRight() {
  this->shape.turnRight();
  if (!this->canMoveShape(0, 0)) {
    this->shape.turnLeft();
    throw CantMoveException();
  }
}

bool GameEnv::canMoveShape(int8_t xChange, int8_t yChange) const {
  const Coordinate mainCoord = this->shape.getCoordinate();
  const auto blocks = this->shape.getBlocks();

  for (size_t x = 0; x < 4; ++x) {
    for (size_t y = 0; y < 4; ++y) {
      if (blocks[y][x] == nullptr) {
        continue;
      }
      Coordinate coord(mainCoord.x + x + xChange, mainCoord.y + y + yChange); // This will overflow
      if (this->hasCollision(coord)) {
        return false;
      }
    }
  }
  return true;
}

void GameEnv::reset() {
  for_each(execution::par_unseq, this->blocks.begin(), this->blocks.end(), [](array<optional<Block>, X_SIZE> &row) {
    for (optional<Block> &block : row) {
      block = std::nullopt;
    }
  });
  this->score = 0;
  this->newShape();
}

void GameEnv::appendShape() {
  const Coordinate coord = this->shape.getCoordinate();
  auto shapeBlocks = this->shape.intoBlocks();

  for (size_t y = 0; y < 4; ++y) {
    for (size_t x = 0; x < 4; ++x) {
      if (!shapeBlocks[y][x].has_value())
        continue;
      this->blocks[coord.y + y][coord.x + x] = std::move(shapeBlocks[y][x]);
    }
  }
}

void GameEnv::newShape() {
  this->shape = std::move(this->nextShape);
  this->nextShape = this->builder.randomShape().build();
  if (!this->canMoveShape(0, 0)) throw GameEnvOverflowException();
}

vector<size_t> GameEnv::getFullRows() const {
  vector<size_t> cleared;

  for (size_t y = 0; y < Y_SIZE; ++y) {
    bool fullRow = true;
    for (auto block : this->blocks[y]) {
      if (!block.has_value()) {
        fullRow = false;
        break;
      }
    };
    if (fullRow) {
      cleared.push_back(y);
    };
  }
  return std::move(cleared);
}

void GameEnv::clearRows(const vector<size_t> rowIdx) noexcept {
  for (size_t cleared = 0; cleared < rowIdx.size(); ++cleared) {
    for (size_t y = rowIdx[cleared] + 1 - cleared; y < Y_SIZE; ++y) {
      this->blocks[y - 1] = std::move(this->blocks[y]);
    }
  };

  if (rowIdx.size() == 4) {
    this->score += 5000;
  } else {
    this->score += rowIdx.size() * 1000;
  }
}

const bool GameEnv::hasCollision(const Coordinate coord) const {
  if (coord.y >= Y_SIZE)
    return false;
  if (coord.x < 0 || coord.y <= 0 || coord.x >= X_SIZE)
    return true;

  const optional<Block> &block = this->blocks[coord.y][coord.x];
  return block.has_value();
}

array<array<const Block*, X_SIZE>, Y_SIZE> GameEnv::getBlocks() const {
  array<array<const Block*, X_SIZE>, Y_SIZE> newArray;
  for (size_t x = 0; x < X_SIZE; x++) {
    for (size_t y = 0; y < Y_SIZE; y++) {
      const optional<Block>& block = this->blocks[y][x];
      if (block) {
        newArray[y][x] = &(*block);
      } else {
        newArray[y][x] = nullptr;
      }
    }
  }
  return std::move(newArray);
}

