#ifndef APP_FACTORY
#define APP_FACTORY

#include <memory>
#include <pugixml.hpp>

#include "App.hpp"

namespace matrix_minds
{
  class AppFactory
  {
  protected:
    pugi::xml_node graphics_node;
    const char *app_name;

    public:
      AppFactory(const char* app_name) : app_name(app_name) {}
      AppFactory(const char* app_name, const char* xml_path) : app_name(app_name) {
        pugi::xml_document doc;
        int res = doc.load_file(xml_path);
        if (!res) throw std::runtime_error("File not present at the requested location");
        this->graphics_node = doc.child(app_name);
      }
      virtual shared_ptr<App> buildApp() const = 0;
  };
}

#endif
