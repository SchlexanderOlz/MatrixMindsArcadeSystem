#ifndef FIELDS 
#define FIELDS 


#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <pugixml.hpp>

#include "DisplayItem.hpp"
#include "GraphicsEngine.hpp"


using namespace std;
using namespace rgb_matrix;

namespace matrix_minds {
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
  TextField(string id, double x, double y, string text, Color color, Color bg_color)
      : PositionalField(std::move(id), x, y), text(std::move(text)), color(color), background_color(bg_color) {}
  TextField(string id, double x, double y, string text)
      : TextField(id, x, y, text, Color(255, 255, 255), Color(0, 0, 0)) {}
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
}
#endif
