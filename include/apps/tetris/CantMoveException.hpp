#ifndef CANTMOVE
#define CANTMOVE

#include <exception>
#include <sstream>

class CantMoveException : std::exception {
  const char* what() const noexcept override {
    return "Cant move to the specified position";
  };
};

#endif
