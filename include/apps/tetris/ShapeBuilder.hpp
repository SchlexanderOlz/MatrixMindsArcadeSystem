#ifndef SHAPEBUILDER
#define SHAPEBUILDER


#include <array>
#include <functional>
#include <random>

#include "Block.hpp"
#include "Shape.hpp"
#include "Utils.hpp"

using namespace std;

namespace tetris {
  class ShapeBuilder {
    private:
      Color current_color;
      Coordinate pos;
      function<MoveStateIterator(const ShapeBuilder*)> state_getter;

      void setColor(Color color);
      MoveStateIterator buildLShapeStates() const;
      MoveStateIterator buildIShapeStates() const;
      MoveStateIterator buildRLShape() const;
      MoveStateIterator buildSquareShape() const;
      MoveStateIterator buildTShape() const;
      MoveStateIterator buildSShape() const;
      MoveStateIterator buildRSShape() const;

      static inline const array<function<MoveStateIterator(const ShapeBuilder*)>, 7> getStateBuilders(){
        return { &ShapeBuilder::buildLShapeStates, &ShapeBuilder::buildIShapeStates, &ShapeBuilder::buildRLShape, &ShapeBuilder::buildSquareShape, &ShapeBuilder::buildTShape, &ShapeBuilder::buildSShape, &ShapeBuilder::buildRSShape };
      }

    public:
      ShapeBuilder() {}
      inline Shape build() { return Shape(this->pos, state_getter(this));};

      inline ShapeBuilder& green() { this->current_color = Color::GREEN; return *this; }
      inline ShapeBuilder& red() { this->current_color = Color::RED; return *this; }
      inline ShapeBuilder& blue() { this->current_color = Color::BLUE; return *this; }
      inline ShapeBuilder& yellow() { this->current_color = Color::YELLOW; return *this; }
      inline ShapeBuilder& magenta() { this->current_color = Color::MAGENTA; return *this; }
      ShapeBuilder& lShape();
      ShapeBuilder& iShape();
      ShapeBuilder& rlShape();
      ShapeBuilder& squareShape();
      ShapeBuilder& tShape();
      ShapeBuilder& sShape();
      ShapeBuilder& rsShape();
      inline ShapeBuilder& position(Coordinate coord) { this->pos = coord; return *this; };
      ShapeBuilder& randomShape();
  };
}
#endif
