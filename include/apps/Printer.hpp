#ifndef PRINTER 
#define PRINTER 

#include <unistd.h>

#include "App.hpp"
#include "Controler.hpp"
#include "TextBuilder.hpp"

using namespace std;

namespace matrix_minds {
  class Printer : public App {
    private:
      TextBuilder builder_;
    public:
      Printer(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler) : App(engine, controler), builder_(TextBuilder()) {}
      void run() override;
      void performAction(const Action action);
  };
}
#endif

