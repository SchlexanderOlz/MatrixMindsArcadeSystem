#ifndef STATIC_GRAPHICS
#define STATIC_GRAPHICS

#include <iostream>
#include <memory>
#include <pugixml.hpp>

#include "Rectangle.hpp"

using namespace std;

namespace matrix_minds
{
  class Field
  {
  private:
  public:
    virtual const vector<Rectangle> getShape() = 0;
  };

  class PositionalField : public Field
  {
  protected:
    string id;
    double x;
    double y;

  public:
    PositionalField(string id, double x, double y) : id(std::move(id)), x(x), y(y) {}
    PositionalField(const pugi::xml_node &node) { this->id = node.attribute("id").as_string(); }
  };

  class TextField : public PositionalField
  {
  protected:
    string text;

  public:
    TextField(string id, double x, double y, string text) : PositionalField(std::move(id), x, y), text(std::move(text)) {}
    const vector<Rectangle> getShape() override;
  };

  class Box : public PositionalField
  {
  protected:
    double height;
    double width;

  public:
    Box(string id, double x, double y, double height, double width) : PositionalField(std::move(id), x, y), height(height), width(width) {}
    const vector<Rectangle> getShape() override;
  };
}

#endif
