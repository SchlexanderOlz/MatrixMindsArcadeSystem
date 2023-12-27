#include "apps/tetris/ShapeBuilder.hpp"

using namespace tetris;

ShapeBuilder &ShapeBuilder::randomShape() {
  auto stateFunctions = ShapeBuilder::getStateBuilders();

  constexpr size_t zero = 0;
  const size_t colorIdx = utils::getRandomNumber(zero, (size_t)Color::MAGENTA);
  const size_t shapeIdx = utils::getRandomNumber(zero, stateFunctions.size() - 1);

  this->current_color = (Color)colorIdx;
  this->state_getter = stateFunctions[shapeIdx];
  return *this;
}

ShapeBuilder &ShapeBuilder::iShape() {
  this->state_getter = &ShapeBuilder::buildIShapeStates;
  return *this;
}

ShapeBuilder &ShapeBuilder::lShape() {
  this->state_getter = &ShapeBuilder::buildLShapeStates;
  return *this;
}

ShapeBuilder& ShapeBuilder::sShape() {
  this->state_getter = &ShapeBuilder::buildSShape;
  return *this;
}

ShapeBuilder& ShapeBuilder::tShape() {
  this->state_getter = &ShapeBuilder::buildTShape;
  return *this;
}

ShapeBuilder& ShapeBuilder::rlShape() {
  this->state_getter = &ShapeBuilder::buildRLShape;
  return *this;
}

ShapeBuilder& ShapeBuilder::rsShape() {
  this->state_getter = &ShapeBuilder::buildRSShape;
  return *this;
}

ShapeBuilder& ShapeBuilder::squareShape() {
  this->state_getter = &ShapeBuilder::buildSquareShape;
  return *this;
}

MoveStateIterator ShapeBuilder::buildLShapeStates() const {
  const MoveState state1 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 0)),
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
  });

  const MoveState state2 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
  });

  const MoveState state3 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(2, 0)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
  });

  const MoveState state4 = MoveState({
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(2, 0)),
  });
  return std::move(MoveStateIterator({state1, state2, state3, state4}));
}

MoveStateIterator ShapeBuilder::buildIShapeStates() const {
  const MoveState state1 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(2, 2)),
      std::make_pair(Block(current_color), Coordinate(3, 2)),
  });

  const MoveState state2 = MoveState({
      std::make_pair(Block(current_color), Coordinate(2, 3)),
      std::make_pair(Block(current_color), Coordinate(2, 2)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 0)),
  });

  const MoveState state3 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
      std::make_pair(Block(current_color), Coordinate(3, 1)),
  });

  const MoveState state4 = MoveState({
      std::make_pair(Block(current_color), Coordinate(1, 3)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
  });
  return std::move(MoveStateIterator({state1, state2, state3, state4}));
}

MoveStateIterator ShapeBuilder::buildRLShape() const {
  const MoveState state1 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 2)),
  });

  const MoveState state2 = MoveState({
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(2, 0)),
  });

  const MoveState state3 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 0)),
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
  });

  const MoveState state4 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
  });
  return std::move(MoveStateIterator({state1, state2, state3, state4}));
}

MoveStateIterator ShapeBuilder::buildSquareShape() const {
  const MoveState state1 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 0)),
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
  });
  return std::move(MoveStateIterator({state1}));
}

MoveStateIterator ShapeBuilder::buildTShape() const {
  const MoveState state1 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
  });

  const MoveState state2 = MoveState({
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
  });


  const MoveState state3 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
  });


  const MoveState state4 = MoveState({
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
  });
  return std::move(MoveStateIterator({state1, state2, state3, state4}));
}


MoveStateIterator ShapeBuilder::buildRSShape() const {
  const MoveState state1 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
  });

  const MoveState state2 = MoveState({
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 2)),
  });

  const MoveState state3 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(2, 0)),
  });

  const MoveState state4 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 0)),
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
  });
  return std::move(MoveStateIterator({state1, state2, state3, state4}));
}


MoveStateIterator ShapeBuilder::buildSShape() const {
  const MoveState state1 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(2, 2)),
  });

  const MoveState state2 = MoveState({
      std::make_pair(Block(current_color), Coordinate(1, 2)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 0)),
  });

  const MoveState state3 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(2, 1)),
  });

  const MoveState state4 = MoveState({
      std::make_pair(Block(current_color), Coordinate(0, 2)),
      std::make_pair(Block(current_color), Coordinate(0, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 1)),
      std::make_pair(Block(current_color), Coordinate(1, 0)),
  });
  return std::move(MoveStateIterator({state1, state2, state3, state4}));
}
