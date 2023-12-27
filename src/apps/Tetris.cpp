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
      this->game.turnShapeRight();
      break;
    case Action::AlternativeLeft: 
      this->game.turnShapeLeft();
      break;
    case Action::Right:
      this->game.moveShapeRight();
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
      this->game.moveShapeLeft();
      break;
    default:
      return;
  }
}

void Tetris::startGame() {
  volatile bool has_ended = false;
  auto joinhandle = thread([this, &has_ended]() {
    while (!has_ended) {
      try {
          this->game.moveShapeDown();
          this->drawState();
          this->engine->show();
      } catch (const CantMoveException& e) {
          try {
            this->game.appendShape();
            this->game.newShape();
            vector<size_t> full = this->game.getFullRows();
            this->game.clearRows(full);
        } catch (const GameEnvOverflowException& e) {
          has_ended = true;
        }
      } 
      usleep(50000);
    }
  });

  while (!has_ended) {
    try {
      this->performIngameAction(this->controler->getAction());
      this->drawState();
      this->engine->show();
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

void Tetris::drawState() const {
  std::cout << "ssoososenbinder" << endl;
  auto blocks = this->game.getBlocks();
  for (size_t y = 0; y < this->game.getSizeY(); ++y) {
    for (size_t x = 0; x < this->game.getSizeX(); ++x) {
      const tetris::Block* block = blocks[y][x];
      if (block == nullptr) continue;
      constexpr float ml = 0.0;
      constexpr float mt = 0.00;
      constexpr float mr = 0.0;
      constexpr float mb = 0.00;

      float x_pos = ((x * (1.0 - ml - mr)) * 2.0) / (float)this->game.getSizeX() + ml - 0.5;
      float y_pos = ((y * (1.0 - mt - mb)) * 2.0) / (float)this->game.getSizeY() + mt - 0.5;
      float width = ((1.0 - ml - mr) / (float)this->game.getSizeX());
      float height = ((1.0 - ml - mr) / (float)this->game.getSizeY());
      std::cout << "X: " << x_pos << " Y: " << y_pos << " Width: " << width << endl;
      Line line(x_pos, y_pos, height, width, Tetris::translateColor(block->getColor()));
      this->engine->render(std::move(line));
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

