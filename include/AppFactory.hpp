#ifndef APP_FACTORY
#define APP_FACTORY

#include <map>
#include <memory>
#include <pugixml.hpp>
#include <cstring>

#include "App.hpp"

using namespace std;

#define CONTENT "content"

namespace matrix_minds {
/**
 * @brief Abstract factory for apps. Currently requires a .xml file for each
 * app.
 */
class AppFactory {
protected:
  const char *app_name;
  StructureNode static_graphics;

  static StructureNode getStaticGraphics(pugi::xml_node node) {
    StructureNode main;
    main.name = node.name();

    std::for_each(node.attributes_begin(), node.attributes_end(), [&main](pugi::xml_attribute attribute){
      main.attributes.emplace(
          std::make_pair(attribute.name(), string(attribute.value())));
    });
    string value = node.child_value();
    if (value != "") main.attributes.emplace(std::make_pair(CONTENT, value));

    std::for_each(node.begin(), node.end(), [&main](pugi::xml_node lable){
      if (strlen(lable.name()) == 0) return;
      main.children.emplace_back(
          std::make_unique<StructureNode>(AppFactory::getStaticGraphics(lable)));
    });
    return main;
  }

public:
  AppFactory(const char *app_name) : app_name(app_name) {}
  AppFactory(const char *app_name, const char *xml_data) : app_name(app_name) {
    pugi::xml_document doc;
    std::cout << xml_data << std::endl;
    pugi::xml_parse_result res = doc.load_buffer(static_cast<const void*>(xml_data), strlen(xml_data));
    if (!res)
      throw std::runtime_error("XML-File Invalid");
    this->static_graphics = AppFactory::getStaticGraphics(doc.child(app_name));
  }
  virtual shared_ptr<App> buildApp() const = 0;
};
} // namespace matrix_minds

#endif
