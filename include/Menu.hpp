#ifndef MENU
#define MENU

#include <vector>
#include <utility>
#include <memory>

#include "App.hpp"
#include "AppFactory.hpp"
#include "DisplayItem.hpp"
#include "GraphicsEngine.hpp"
#include "Controler.hpp"
#include "StaticGraphics.hpp"

using namespace std;

namespace matrix_minds {
  class Menu : public App
  {
  private:
    vector<pair<unique_ptr<AppFactory>, vector<shared_ptr<DisplayItem>>>> apps; // Screams for an iterator
    size_t focused_app_idx = 0;

    void drawState();

  public:
    Menu(shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler) : App(engine, controler, StaticGraphics()) {}
    void run() override;
    void performAction(const Action action);
    inline void registerApp(unique_ptr<AppFactory> factory, vector<shared_ptr<DisplayItem>> icon, string name) { this->apps.push_back(std::make_pair(std::move(factory), icon)); }
  };
}
#endif // MENU
