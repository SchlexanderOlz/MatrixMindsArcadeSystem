#include "KeyboardControler.hpp"

using namespace matrix_minds;

Action KeyboardControler::getAction() {
  switch (KeyboardControler::getch()) {
    case '\n':
      return Action::Confirm;
    case 'q':
      return Action::Quit;
    case 68: 
      return Action::Left;
    case 66:
      return Action::Down;
    case 67: 
      return Action::Right;
    case 'a':
      return Action::AlternativeLeft;
    case 'd':
      return Action::AlternativeRight;
  }
  return Action::Invalid;
}
