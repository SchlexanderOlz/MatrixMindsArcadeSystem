#ifndef TETRIS_FACTORY
#define TETRIS_FACTORY

#include <memory>
#include <fstream>

#include "../AppFactory.hpp"
#include "Tetris.hpp"
#include "TetrisContent.hpp"

namespace matrix_minds {
class TetrisFactory : public AppFactory {
private:
  shared_ptr<GraphicsEngine> engine;
  shared_ptr<Controler> controler;

public:
  TetrisFactory(const char *app_name, const char *xml_path,
                shared_ptr<GraphicsEngine> engine,
                shared_ptr<Controler> controler)
      : engine(engine), controler(controler), AppFactory(xml_path, app_name) {}

  TetrisFactory(shared_ptr<GraphicsEngine> engine,
                shared_ptr<Controler> controler)
      : engine(engine), controler(controler), AppFactory("Tetris", tetris_XML) {}
  inline shared_ptr<App> buildApp() const override {
    return std::shared_ptr<App>((App *)new Tetris(
        this->engine, this->controler, StaticGraphics(&this->static_graphics)));
  }
};
} // namespace matrix_minds

#endif
