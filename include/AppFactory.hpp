#ifndef APP_FACTORY
#define APP_FACTORY

#include <memory>

#include "App.hpp"

namespace matrix_minds {
  class AppFactory {
    public:
      virtual shared_ptr<App> buildApp() = 0;
  };
}

#endif
