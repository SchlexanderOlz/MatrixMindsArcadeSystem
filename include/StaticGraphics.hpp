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

namespace matrix_minds {
class FieldTypes {
private:
  static vector<unique_ptr<FieldFactory>> fields_;

public:
  static void addField(unique_ptr<FieldFactory> field) {
    FieldTypes::fields_.push_back(std::move(field));
  }
  static shared_ptr<FieldFactory> get(const string &field_name);
};

class StaticGraphics {
private:
  vector<unique_ptr<Field>> active_fields_;

public:
  void instanciateField(const string &field_name,
                        const map<string, string> args);
  void display(shared_ptr<GraphicsEngine> engine) const;
};

class Field {
private:
public:
  virtual void apply(shared_ptr<GraphicsEngine> engine) const = 0;
};

class FieldFactory {
protected:
  const string field_name_;

public:
  FieldFactory(const string field_name) : field_name_(std::move(field_name)) {}
  inline virtual const string &getIdentifier() const { return field_name_; };
  virtual unique_ptr<Field> build(map<string, string> args) const = 0;
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

class PositionalFieldFactory : public FieldFactory {
public:
  PositionalFieldFactory(string name) : FieldFactory(std::move(name)){};
  unique_ptr<Field> build(map<string, string> args) const override;
};

class TextFieldFactory : public PositionalFieldFactory {
public:
  TextFieldFactory() : PositionalFieldFactory("textfield"){};
  unique_ptr<Field> build(map<string, string> args) const override;
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
  void apply(shared_ptr<GraphicsEngine> engine) const;
};
} // namespace matrix_minds

#endif
