#ifndef KEYBOARD_CONTROLER
#define KEYBOARD_CONTROLER

#include "Controler.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>

namespace matrix_minds {
/**
 * @brief Handles keyboard-presses and maps them to unambigious, standardized
 * Action type which is handled the same way by all ActionHandlers.
 */
class KeyboardControler : public Controler {
private:
/**
 * @brief Records a keypress from the terminal. Also records arrows and other symbols.
*/
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
/**
 * @brief Blocks until a new action is detected by the Controler.
*/
  Action getAction() override;
};
} // namespace matrix_minds

#endif
