#ifndef MENU
#define MENU

#include <vector>
#include <utility>

#include "App.hpp"
#include "AppFactory.hpp"
#include "GraphicsEngine.hpp"

using namespace std;

namespace matrix_minds {
  typedef vector<Line> Icon;

  class Menu {
    private:
      shared_ptr<GraphicsEngine> engine;
      vector<pair<shared_ptr<AppFactory>, Icon>> apps;
    public:
      Menu(shared_ptr<GraphicsEngine> engine) : engine(engine) {}
      void render();
      inline void registerApp(shared_ptr<AppFactory> factory, Icon icon) { this->apps.push_back(std::make_pair(factory, icon)); }
  };
}
#endif // MENU
