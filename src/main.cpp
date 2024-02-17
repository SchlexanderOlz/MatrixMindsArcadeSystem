#include <iostream>
#include <signal.h>

#include "Menu.hpp"
#include "KeyboardControler.hpp"
#include "apps/TetrisFactory.hpp"
#include "Triangle.hpp"

using namespace matrix_minds;

static volatile bool interrupt_received = false;
static void interruptHandler(int signo) {
  exit(0);
  interrupt_received = true;
}

int main (int argc, char *argv[]) {
  RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;

  matrix_options.rows = 32;
  matrix_options.cols = 32;
  matrix_options.chain_length = 1;
  matrix_options.parallel = 1;

  unique_ptr<RGBMatrix> matrix = unique_ptr<RGBMatrix>(RGBMatrix::CreateFromOptions(matrix_options, runtime_opt));
  if (matrix == NULL)
    return 1;

  printf("Size: %dx%d. Hardware gpio mapping: %s\n",
         matrix->width(), matrix->height(), matrix_options.hardware_mapping);


  signal(SIGTERM, interruptHandler);
  signal(SIGINT, interruptHandler);

  printf("Press <CTRL-C> to exit and reset LEDs\n");

  shared_ptr<GraphicsEngine> engine = std::make_shared<GraphicsEngine>(std::move(matrix));
  shared_ptr<Controler> controler = std::make_shared<KeyboardControler>();
  Triangle tangle({ Position(1.0, -1.0), Position(1.0, 1.0), Position(0.0, 1.0) }, Color(100, 100, 100));
  engine->render(&tangle);
  engine->show();
  while (true) {}
  #ifdef SOS
  Tetris menu(engine, controler);

  unique_ptr<TetrisFactory> tetris_factory = std::make_unique<TetrisFactory>(engine, controler);
  Line tmp(0.1, 0.1, 0.1, 0.1, Color(0, 100, 0));
  Line tmp2(0.1, 0.2, 0.1, 0.1, Color(0, 0, 100));
  menu.registerApp(std::move(tetris_factory), {tmp, tmp2});
  menu.run();

  #endif

  printf("Received CTRL-C. Exiting.\n");
  return 0;
}
