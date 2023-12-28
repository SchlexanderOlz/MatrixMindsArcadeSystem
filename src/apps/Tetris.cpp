#include "apps/Tetris.hpp"

using namespace matrix_minds;

constexpr double ml = 0.2;
constexpr double mt = 0.0;
constexpr double mr = 0.2;
constexpr double mb = 0.0;

constexpr double offset = 0.6;


void Tetris::run() {
  this->drawTitleScreen();
}

void Tetris::drawTitleScreen() {
  for (;;) {
    this->performTitleScreenAction(this->controler->getAction());
  };
}

void Tetris::performTitleScreenAction(const Action action) {
  switch (action) {
    case Action::Confirm:
      return startGame();
    case Action::Quit:
      return exitApp();
    case Action::Invalid:
      return;
    default:
      return;
  }
}

void Tetris::performIngameAction(const Action action) {
  switch (action) {
    case Action::AlternativeRight:
      try {
        this->game.turnShapeRight();
      } catch (CantMoveException) {}
      break;
    case Action::AlternativeLeft: 
      try {
        this->game.turnShapeLeft();
      } catch (CantMoveException) {}
      break;
    case Action::Right:
      try {
        this->game.moveShapeRight();
      } catch (CantMoveException) {}
      break;
    case Action::Down:
      try {
        this->game.moveShapeDown();
      } catch (CantMoveException) {
        this->game.appendShape();
        this->game.newShape();
        vector<size_t> full = this->game.getFullRows();
        this->game.clearRows(full);
      }
      break;
    case Action::Left:
      try {
        this->game.moveShapeLeft();
      } catch (CantMoveException) {}
      break;
    default:
      return;
  }
}

void Tetris::startGame() {
  volatile bool has_ended = false;
  auto joinhandle = thread([this, &has_ended]() {
    while (!has_ended) {
      unique_lock<mutex> lock(this->mtx);
      try {
          this->game.moveShapeDown();
      } catch (CantMoveException) {
          try {
            this->game.appendShape();
            this->game.newShape();
            vector<size_t> full = this->game.getFullRows();
            this->game.clearRows(full);
        } catch (const GameEnvOverflowException& e) {
          has_ended = true;
        }
      } 
      this->drawState();
      this->engine->show();
      lock.unlock();
      usleep(500000);
    }
  });

  while (!has_ended) {
    try {
      Action action = this->controler->getAction();
      unique_lock<mutex> lock(this->mtx);
      this->performIngameAction(action);
      this->drawState();
      this->engine->show();
      lock.unlock();
      usleep(100);
    } catch (GameEnvOverflowException) { has_ended = true; }
    catch (CantMoveException) {}
  }
  joinhandle.join();
  this->endGame();
}

void Tetris::endGame() {
  // Show statistics of the game here
  // + leaderboard and new Highscore stuff

}

void Tetris::mapBlock(const tetris::Block* block, uint x, uint y) const {
  this->mapBlock(block, x, y, 0.0, 0.0);
}

void Tetris::mapBlock(const tetris::Block* block, uint x, uint y,  const double x_offset, const double y_offset) const {
  double x_pos = ((x * (1.0 - ml - mr)) * 2.0) / (double)this->game.getSizeX() + offset + x_offset - 1.0;
  double y_pos = ((y * (1.0 - mt - mb)) * 2.0) / (double)this->game.getSizeY() + y_offset - 1.0;
  double width = ((1.0 - ml - mr) / (double)this->game.getSizeX()) / 2.0;
  double height = ((1.0 - mt - mb) / (double)this->game.getSizeY()) / 2.0;
  Line line(x_pos, y_pos, height, width, Tetris::translateColor(block->getColor()));
  this->engine->render(std::move(line));
}

void Tetris::mapShape(const tetris::Shape& shape, const double x_offset, const double y_offset) const {
  auto shape_coord = shape.getCoordinate();
  auto shape_blocks = shape.getBlocks();

  for (size_t y = 0; y < shape_blocks.size(); ++y) {
    for (size_t x = 0; x < shape_blocks[0].size(); ++x) {
      const tetris::Block* block = shape_blocks[y][x];
      if (block == nullptr) continue;
      this->mapBlock(block, x + shape_coord.x, y + shape_coord.y, x_offset, y_offset);
    }
  }
}

void Tetris::mapShape(const tetris::Shape& shape) const {
  this->mapShape(shape, 0.0, 0.0);
}

void Tetris::drawState() const {
  auto blocks = this->game.getBlocks();
  const tetris::Shape& shape = this->game.getShape();
  this->mapShape(this->game.getShape());

  this->mapShape(this->game.getNextShape(), -1.16, -0.28);
  auto shape_coord = shape.getCoordinate();
  auto shape_blocks = shape.getBlocks();

  for (size_t y = 0; y <= this->game.getSizeY(); ++y) {
    for (size_t x = 0; x <= this->game.getSizeX(); ++x) {
      const tetris::Block* block = blocks[y][x];
      if (block == nullptr) continue;
      this->mapBlock(block, x, y);
    }
  }
  constexpr double height = 1.95 - mt - 1.0;
  const double block_width = 1.0 / this->engine->getSizeX();
  const double block_height = 1.0 / this->engine->getSizeY();

  constexpr double hor_length = 1.1 - mr - ml;
  constexpr double x_offset = -1.05 + offset;
  constexpr double y_offset = -0.9 - mt;

  const Color color = Color(100, 100, 100);

  Line line_1(x_offset, y_offset, block_height, hor_length, color);
  this->engine->render(std::move(line_1));

  Line line_2(x_offset, y_offset, height, block_width, color);
  this->engine->render(std::move(line_2));

  Line line_3(ml + offset + 0.1, y_offset, height, block_width, color);
  this->engine->render(std::move(line_3));

  Line line_4(x_offset, 0.95 - mt, block_height, hor_length, color);
  this->engine->render(std::move(line_4));
}

Color Tetris::translateColor(const tetris::Color color) {
  switch (color) {
    case tetris::Color::GREEN: return Color(0, 200, 0);
    case tetris::Color::RED: return Color(200, 0, 0);
    case tetris::Color::BLUE: return Color(0, 0, 200);
    case tetris::Color::YELLOW: return Color(100, 0, 200);
    case tetris::Color::MAGENTA: return Color(50, 20, 200);
  }
}

