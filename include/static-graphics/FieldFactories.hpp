#ifndef FIELD_FACTORIES
#define FIELD_FACTORIES

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <pugixml.hpp>

#include "DisplayItem.hpp"
#include "GraphicsEngine.hpp"
#include "Fields.hpp"


using namespace std;
using namespace rgb_matrix;

namespace matrix_minds {
class Field;

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
  PositionalFieldFactory(const string name) : FieldFactory(std::move(name)){};
};

class TextFieldFactory : public PositionalFieldFactory {
public:
  TextFieldFactory() : PositionalFieldFactory("text"){};
  unique_ptr<Field> build(map<string, string> args) const override;
};

class TriangleFieldFactory : public PositionalFieldFactory {
public:
  TriangleFieldFactory() : PositionalFieldFactory("triangle") {};
  unique_ptr<Field> build(map<string, string> args) const override;
};

class BoxFieldFactory : public PositionalFieldFactory {
public:
  BoxFieldFactory() : PositionalFieldFactory("box"){};
  unique_ptr<Field> build(map<string, string> args) const override;
};
}
#endif // !FIELD_FACTORY
