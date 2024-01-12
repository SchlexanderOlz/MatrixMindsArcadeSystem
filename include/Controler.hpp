#ifndef CONTROLER
#define CONTROLER

namespace matrix_minds
{
  enum class Action
  {
    Invalid,
    Confirm,
    Stop,
    Quit,
    Right,
    Left,
    Down,
    Up,
    AlternativeRight,
    AlternativeLeft
  };

  class Controler
  {
  public:
    virtual Action getAction() = 0;
  };
}

#endif
