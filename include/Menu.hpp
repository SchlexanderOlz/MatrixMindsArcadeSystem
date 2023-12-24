#ifdef MENU
#define MENU

#include <vector>

#include "App.hpp"
#include "GraphicsEngine.hpp"

using namespace std;

namespace matrix_minds {
  class Menu {
    private:
      shared_ptr<GraphicsEngine> engine;
      vector<App> apps; // Size will probably be statically known
    public:
      void render();
  }
}
#endif // MENU
