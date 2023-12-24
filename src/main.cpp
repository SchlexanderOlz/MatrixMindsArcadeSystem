#include <iostream>
#include <signal.h>
#include "../include/GraphicsEngine.hpp"


static volatile bool interrupt_received = false;
static void interruptHandler(int signo) {
  interrupt_received = true;
}

int main (int argc, char *argv[]) {
  const char *demo_parameter = NULL;
  RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;

  matrix_options.rows = 32;
  matrix_options.cols = 32;
  matrix_options.chain_length = 1;
  matrix_options.parallel = 1;

  if (optind < argc) {
    demo_parameter = argv[optind];
  }

  RGBMatrix *matrix = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
  if (matrix == NULL)
    return 1;

  printf("Size: %dx%d. Hardware gpio mapping: %s\n",
         matrix->width(), matrix->height(), matrix_options.hardware_mapping);

  Canvas *canvas = matrix;

  signal(SIGTERM, interruptHandler);
  signal(SIGINT, interruptHandler);

  printf("Press <CTRL-C> to exit and reset LEDs\n");

  delete canvas;

  printf("Received CTRL-C. Exiting.\n");
  return 0;
}
