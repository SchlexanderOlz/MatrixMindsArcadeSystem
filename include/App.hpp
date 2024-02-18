#ifndef APP
#define APP

#include <memory>

#include "DisplayItem.hpp"
#include "GraphicsEngine.hpp"
#include "Controler.hpp"
#include "StaticGraphics.hpp"

using namespace std;

namespace matrix_minds
{
  /**
   * @brief Abstract App interface
  */
  class App
  {
  protected:
    shared_ptr<GraphicsEngine> engine_;
    shared_ptr<Controler> controler_;
    StaticGraphics static_graphics_;
  public:
    App(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler, StaticGraphics static_graphics) : engine_(engine), controler_(controler), static_graphics_(std::move(static_graphics)) {}

    virtual void run() = 0;
  };
}
#endif
