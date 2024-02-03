#ifndef MENU
#define MENU

#include <vector>
#include <utility>

#include "App.hpp"
#include "AppFactory.hpp"
#include "GraphicsEngine.hpp"
#include "Controler.hpp"

using namespace std;

namespace matrix_minds {
  typedef vector<Rectangle> Icon;

  class Menu : public App
  {
  private:
    vector<pair<unique_ptr<AppFactory>, Icon>> apps; // Screams for an iterator
    size_t focused_app_idx = 0;

    void drawState();

  public:
    Menu(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler) : App(engine, controler) {}
    void run() override;
    void performAction(const Action action);
    inline void registerApp(unique_ptr<AppFactory> factory, Icon icon, string name) { this->apps.push_back(std::make_pair(std::move(factory), icon)); }
  };
}
#endif // MENU
