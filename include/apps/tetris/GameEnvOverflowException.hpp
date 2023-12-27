#ifndef GAMEENVOVERFLOW 
#define GAMEENVOVERFLOW

#include <exception>
#include <sstream>

class GameEnvOverflowException : std::exception {
  const char* what() const noexcept override {
    return "New Shape could not be spawned";
  };
};

#endif
