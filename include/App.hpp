#ifndef APP
#define APP

#include <memory>

#include "GraphicsEngine.hpp"
#include "DisplayItem.hpp"
#include "Controler.hpp"

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
    App(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler) : engine_(engine), controler_(controler) {}

  public:
    virtual void run() = 0;
  };
}
#endif
