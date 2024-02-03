#ifndef TETRIS_FACTORY
#define TETRIS_FACTORY

#include <memory>

#include "Tetris.hpp"
#include "../AppFactory.hpp"

namespace matrix_minds {
  class TetrisFactory : public AppFactory {
    private:
      shared_ptr<GraphicsEngine> engine;
      shared_ptr<Controler> controler;
    public:
      TetrisFactory(const char* xml_path, const char* app_name, shared_ptr<GraphicsEngine> engine, shared_ptr<Controler> controler) : engine(engine), controler(controler), AppFactory(xml_path, app_name) {}
      inline shared_ptr<App> buildApp() const override { return shared_ptr<App>((App*)new Tetris(this->engine, this->controler)); }
  };
}

#endif
