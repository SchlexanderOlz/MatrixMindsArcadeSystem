#ifndef TETRIS
#define TETRIS

#include <unistd.h>
#include <thread>

#include "App.hpp"
#include "tetris/Tetris.hpp"
#include "Controler.hpp"

using namespace std;

namespace matrix_minds {
  class Tetris : public App {
    private:
      tetris::GameEnv game;
      
      volatile bool exit = false;

      void drawTitleScreen();
      void runGame();
      void performTitleScreenAction(const Action action);
      void performIngameAction(const Action action);
      
      void endGame();
      void startGame();
      inline void exitApp() { this->exit = true; }

      static Color translateColor(const tetris::Color color);
    public:
      Tetris(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler) : App(engine, controler), game(tetris::GameEnv()) {}
      void run() override;
      void drawState() const;
  };
}
#endif

