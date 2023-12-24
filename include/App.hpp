#ifndef APP
#define APP

#include <memory>

#include "GraphicsEngine.hpp"
#include "DisplayItem.hpp"

using namespace std;

namespace matrix_minds {
  class App {
    protected:
      shared_ptr<GraphicsEngine> engine;
    public:
      virtual void run() = 0;
  };
}
#endif

