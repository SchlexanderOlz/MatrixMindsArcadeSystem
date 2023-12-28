#include "apps/Tetris.hpp"

using namespace matrix_minds;


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
  constexpr double ml = 0.2;
  constexpr double mt = 0.0;
  constexpr double mr = 0.2;
  constexpr double mb = 0.0;

  double x_pos = ((x * (1.0 - ml - mr)) * 2.0) / (double)this->game.getSizeX() + ml - 1.0;
  double y_pos = ((y * (1.0 - mt - mb)) * 2.0) / (double)this->game.getSizeY() + mt - 1.0;
  double width = ((1.0 - ml - mr) / (double)this->game.getSizeX()) / 2.0;
  double height = ((1.0 - mt - mb) / (double)this->game.getSizeY()) / 2.0;
  Line line(x_pos, y_pos, height, width, Tetris::translateColor(block->getColor()));
  this->engine->render(std::move(line));

}

void Tetris::drawState() const {
  auto blocks = this->game.getBlocks();
  tetris::Shape shape = this->game.getShape();
  auto shape_coord = shape.getCoordinate();
  auto shape_blocks = shape.getBlocks();

  for (size_t y = 0; y < shape_blocks.size(); ++y) {
    for (size_t x = 0; x < shape_blocks[0].size(); ++x) {
      const tetris::Block* block = shape_blocks[y][x];
      if (block == nullptr) continue;
      this->mapBlock(block, x + shape_coord.x, y + shape_coord.y);
    }
  }

  for (size_t y = 0; y <= this->game.getSizeY(); ++y) {
    for (size_t x = 0; x <= this->game.getSizeX(); ++x) {
      const tetris::Block* block = blocks[y][x];
      if (block == nullptr) continue;
      this->mapBlock(block, x, y);
    }
  }
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

