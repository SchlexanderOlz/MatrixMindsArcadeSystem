#ifndef KEYBOARD_CONTROLER
#define KEYBOARD_CONTROLER

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Controler.hpp"

namespace matrix_minds {
  class KeyboardControler : public Controler {
    private:
    static char getch() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
      }
      public:
        Action getAction() override;
    };
}

#endif
