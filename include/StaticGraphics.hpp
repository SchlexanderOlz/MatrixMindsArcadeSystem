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

using namespace std;
using namespace rgb_matrix;

namespace matrix_minds {
class GraphicsEngine;

class StructureNode {
public:
  vector<unique_ptr<StructureNode>> children;
  string name;
  map<string, string> attributes;
};

#pragma region Fields
class Field {
private:
public:
  virtual void apply(shared_ptr<GraphicsEngine> engine) const = 0;
};

class PositionalField : public Field {
protected:
  string id;
  double x;
  double y;

public:
  inline const string &getId() const { return this->id; }
  inline double getX() const { return this->x; }
  inline double getY() const { return this->y; }
  PositionalField(string id, double x, double y)
      : id(std::move(id)), x(x), y(y) {}
  PositionalField(const pugi::xml_node &node) {
    this->id = node.attribute("id").as_string();
  }
};

class TextField : public PositionalField {
protected:
  string text;
  Color color;
  Color background_color;

public:
  inline const Color &getColor() const { return this->color; }
  inline const Color &getBGColor() const { return this->background_color; }
  inline const string &getText() const { return this->text; }
  TextField(string id, double x, double y, string text)
      : PositionalField(std::move(id), x, y), text(std::move(text)) {}
  void apply(shared_ptr<GraphicsEngine> engine) const;
};

class Box : public PositionalField {
protected:
  double height;
  double width;
  Color color;

public:
  Box(string id, double x, double y, double height, double width, Color color)
      : PositionalField(std::move(id), x, y), height(height), width(width),
        color(color) {}

  Box(string id, double x, double y, double height, double width)
      : Box(id, x, y, height, width, Color(255, 255, 255)) {}
  void apply(shared_ptr<GraphicsEngine> engine) const;
};
#pragma endregion

#pragma region FieldFactories
class FieldFactory {
protected:
  const string field_name_;

public:
  FieldFactory(const string field_name) : field_name_(std::move(field_name)) {}
  inline virtual const string &getIdentifier() const { return field_name_; };
  virtual unique_ptr<Field> build(map<string, string> args) const = 0;
};

class PositionalFieldFactory : public FieldFactory {
public:
  PositionalFieldFactory(string name) : FieldFactory(std::move(name)){};
};

class TextFieldFactory : public PositionalFieldFactory {
public:
  TextFieldFactory() : PositionalFieldFactory("textfield"){};
  unique_ptr<Field> build(map<string, string> args) const override;
};

class BoxFieldFactory : public PositionalFieldFactory {
public:
  BoxFieldFactory() : PositionalFieldFactory("box"){};
  unique_ptr<Field> build(map<string, string> args) const override;
};
#pragma endregion

/**
 * @brief Provides graphics which can be statically rendered through an xml
 * file. This class contains the parsed contents of the xml file.
 */
class StaticGraphics {
private:
  vector<unique_ptr<Field>> active_fields_;

public:
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
  void loadFromStructure(const StructureNode* node);
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
  static shared_ptr<FieldFactory> get(const string &field_name);
};
} // namespace matrix_minds

#endif
