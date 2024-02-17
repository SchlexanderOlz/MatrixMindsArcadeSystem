#ifndef APP_FACTORY
#define APP_FACTORY

#include <map>
#include <memory>
#include <pugixml.hpp>

#include "App.hpp"

using namespace std;

namespace matrix_minds {
/**
 * @brief Abstract factory for apps. Currently requires a .xml file for each
 * app.
 */
class AppFactory {
protected:
  const char *app_name;

  static StructureNode getStaticGraphics(pugi::xml_node node) {
    StructureNode main;
    main.name = node.name();
    for (const auto& attribute : node.attributes()) {
      main.attributes.emplace(std::make_pair(attribute.name(), string(attribute.as_string())));
    }
    for (const auto& lable : node.children()) {
        main.children.emplace_back(unique_ptr<StructureNode>(AppFacotry::getStaticGraphics(lable)));
    }
    return main;
  }

  void loadStaticGraphics(const StructureNode& node) {
    StaticGraphics graphics;
    graphics.instanciateField(node.name, node.attributes);
  }

public:
  AppFactory(const char *app_name) : app_name(app_name) {}
  AppFactory(const char *app_name, const char *xml_path) : app_name(app_name) {
    pugi::xml_document doc;
    int res = doc.load_file(xml_path);
    if (!res)
      throw std::runtime_error("XML-Filed not found at the specified location");

    this->loadStaticGraphics(doc.child(app_name));
  }
  virtual shared_ptr<App> buildApp() const = 0;
};
} // namespace matrix_minds

#endif
