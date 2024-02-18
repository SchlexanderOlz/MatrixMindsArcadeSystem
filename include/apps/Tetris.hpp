#ifndef TETRIS
#define TETRIS

#include <thread>
#include <unistd.h>

#include "App.hpp"
#include "Controler.hpp"
#include "tetris/Tetris.hpp"

using namespace std;

namespace matrix_minds {
/**
 * @brief Implementation of Tetris on the RGB-Matrix
 */
class Tetris : public App {
private:
  tetris::GameEnv game;
  mutex mtx;

  volatile bool exit = false;

  void drawTitleScreen();
  void runGame();
  /**
   * @brief Takes a captured action and modifies the state of
   * only the title-screen. This should only be used on the title-screen. For
   * ingame actions use performIngameAction.
   */
  void performTitleScreenAction(const Action action);

  /**
   * @brief Takes a captured action and modifies the state of
   * the game.
   */
  void performIngameAction(const Action action);

  void endGame();
  void startGame();
  /**
   * @brief Does not directly exit the app. Sets a flag to be checked for a
   * correct end of the app.
   */
  inline void exitApp() { this->exit = true; }

  /**
   * @brief Translates a tetris Color into a RGB-Matrix Color
   */
  static Color translateColor(const tetris::Color color);

  /**
   * @brief Maps a block from the tetris-range to the relative -1 to 1 positions
   * of the GraphicsEngine.
   */
  void mapBlock(const tetris::Block *block, uint x, uint y,
                const double y_offset, const double x_offset) const;
  void mapBlock(const tetris::Block *block, uint x, uint y) const;

  /**
   * @brief Maps a shape from the tetris-range, to the relative -1 to 1
   * positions of the GraphicsEngine and then directly draws those to it,
   * changing the current buffer of the engine.
   */
  void mapShape(const tetris::Shape &shape, const double x_offset,
                const double y_offset) const;
  void mapShape(const tetris::Shape &shape) const;

public:
  Tetris(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler, StaticGraphics graphics)
      : App(engine, controler, std::move(graphics)), game(tetris::GameEnv()) {}
  void run() override;
  /**
   * @brief Draws the current state of the game directly to the graphicsEngine.
   */
  void drawState() const;
};
} // namespace matrix_minds
#endif
