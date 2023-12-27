#ifndef GAMEENV 
#define GAMEENV

#define X_SIZE 32 // TMP
#define Y_SIZE 32 // TMP


#include <array>
#include <memory>
#include <mutex>
#include <optional>
#include <chrono>
#include <thread>
#include <algorithm>
#include <execution>
#include <parallel/for_each.h>

#include "Block.hpp"
#include "Shape.hpp"
#include "Coordinate.hpp"
#include "ShapeBuilder.hpp"
#include "CantMoveException.hpp"
#include "GameEnvOverflowException.hpp"

using namespace std;

namespace tetris {

  /*
   * @brief The managed game-field which contains the tetris-logic
   */
  class GameEnv {
    private:
      /* These blocks are represented as a Matrix which displays the "virtual"
      game field*/
      array<array<optional<Block>, X_SIZE>, Y_SIZE> blocks;
      ShapeBuilder builder;
      Shape shape;
      Shape nextShape;
      size_t score;

      bool canMoveShape(int8_t xChange, int8_t yChange) const;

    public:
      GameEnv(const GameEnv&) = delete;
      GameEnv() : builder(ShapeBuilder()), shape(builder.randomShape().position(Coordinate(X_SIZE / 2, Y_SIZE - 3)).build()), nextShape(this->builder.randomShape().build()) {}

      static constexpr size_t getSizeX() { return X_SIZE - 1; }
      static constexpr size_t getSizeY() { return Y_SIZE - 1; }
      /*
       * @brief Provides the logic for calculating the current level
       * @returns size_t -> The current level
       */
      inline size_t getLevel() const { return score / 10000; }

      /*
       * @brief Returns the current score 
       * @returns size_t -> The current level
       */
      inline size_t getScore() const { return score; }

      /*
       * @brief Replaces the current shape with nextShape and gives nextShape a new instance of a random shape
       */
      void newShape();

      /*
       * @brief Checks if there is a Block on the given "coord" position
       * @return bool -> Is there a collision or not
       */
      const bool hasCollision(const Coordinate coord) const;
      
      /*
       * @brief Returns the current shape
       * @return <
       */
      inline const Shape& getShape() const { return this->shape; };

      /*
       * @brief Return the next shape
       * @return <
       */
      inline const Shape& getNextShape() const { return this->nextShape; }

      /*
       * @brief Moves the shape down by 1 in the y-direction
       * @throws CantMoveException
       */
      void moveShapeDown();

      /*
       * @brief Moves the shape right by 1 in the x-direction
       * @throws CantMoveException
       */
      void moveShapeRight();

      /*
       * @brief Moves the shape left by 1 in the x-direction
       * @throws CantMoveException
       */
      void moveShapeLeft();

      /*
       * @brief Turns the shape left by 1 
       * @throws CantMoveException
       */
      void turnShapeLeft();

      /*
       * @brief Turns the shape right by 1
       * @throws CantMoveException
       */
      void turnShapeRight();

      /*
       * @brief Empties the game environment
       */
      void reset();

      /*
       * @brief Embeds the current shape into the game environment
       */
      void appendShape();

      /*
       * @brief Move all rows above n down to n
       * @param rowIdx The y-index of the row
       */
      void clearRows(const vector<size_t> rowIdx) noexcept;

      /*
       * @brief Checks which lines are full
       * @returns vector<size_t> All rows which contain a continous line of blocks in the x-direction
       */
      vector<size_t> getFullRows() const;

      /*
       * @brief Returns all blocks which are embeded into the game-environment
       * @returns ...array<Block*>... The blocks which are contained in the game-environment
       */
      array<array<const Block*, X_SIZE>, Y_SIZE> getBlocks() const;
  };
}
#endif
