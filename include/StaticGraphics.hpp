#ifndef STATIC_GRAPHICS
#define STATIC_GRAPHICS

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <pugixml.hpp>

#include "DisplayItem.hpp"
#include "GraphicsEngine.hpp"
#include "Rectangle.hpp"
#include "static-graphics/Fields.hpp"
#include "static-graphics/FieldFactories.hpp"

using namespace std;
using namespace rgb_matrix;

namespace matrix_minds {
class GraphicsEngine;
class FieldFactory;
class Field;

class StructureNode {
public:
  vector<unique_ptr<StructureNode>> children;
  string name;
  map<string, string> attributes;
};

/**
 * @brief Provides graphics which can be statically rendered through an xml
 * file. This class contains the parsed contents of the xml file.
 */
class StaticGraphics {
private:
  vector<unique_ptr<Field>> active_fields_;

public:
  StaticGraphics(const StructureNode* node) { this->loadStructure(node); }
  StaticGraphics() : active_fields_() {}
  /**
   * @brief Adds a new field to be displayed by name.
   * @param field_name Name as an xml, of the field
   * @param args Attribtues of as given in the xml tag. The map should be
   * created from f.e. a xml node which contains the tag and its attributes.
   * @throws runtime_exception if field does not exist
   * @throws runtime_exception if not all attributes which are required for the
   * field were given.
   */
  void instanciateField(const string &field_name,
                        const map<string, string> args);

  void loadStructure(const StructureNode* node);
  /**
   * @brief Displays all contents of the StaticGraphic to the given
   * GraphicsEngine
   * @param engine GraphicsEngine which contains the active canvas. The shapes
   * and figures of the Staticgraphic are rendered into this engine.
   */
  void display(shared_ptr<GraphicsEngine> engine) const;
};

/**
 * @brief Contains all valid xml fields with their respective name.
*/
class FieldTypes {
private:
  static vector<unique_ptr<FieldFactory>> fields_;
public:
/**
 * @brief Adds another field-factory to the valid fields. Fields are recommended be added at the start of the application (Not required).
 * @param field Pointer to the factory which is appended to the valid fields. Ownership of the factory is given to this class.
*/
  static void addField(unique_ptr<FieldFactory> field) {
    FieldTypes::fields_.push_back(std::move(field));
  }
  /**
   * @brief Returns a factory by a given identifier.
   * @param field_name The unique identifier by which the field can be identified in xml.
  */
  static FieldFactory* get(const string &field_name);
};
} // namespace matrix_minds

#endif
