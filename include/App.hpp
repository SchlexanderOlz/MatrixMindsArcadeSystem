#ifndef APP
#define APP

#include <memory>

#include "GraphicsEngine.hpp"
#include "DisplayItem.hpp"
#include "Controler.hpp"

using namespace std;

namespace matrix_minds {
  class App {
    protected:
      shared_ptr<GraphicsEngine> engine;
      shared_ptr<Controler> controler;
      App(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler) : engine(engine), controler(controler) {}
    public:
      virtual void run() = 0;
  };
}
#endif

