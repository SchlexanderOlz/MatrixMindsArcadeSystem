#include "static-graphics/FieldFactories.hpp"

using namespace matrix_minds;

unique_ptr<Field> TextFieldFactory::build(map<string, string> args) const {
  // Maybe make this into a private constructor
  string id = args.find("id")->second;
  double x = std::stod(args.find("x")->second);
  double y = std::stod(args.find("y")->second);
  string content = args.find("content")->second;
  return std::make_unique<TextField>(id, x, y, content);
}

unique_ptr<Field> BoxFieldFactory::build(map<string, string> args) const {
  // Maybe make this into a private constructor
  string id = args.find("id")->second;
  double x = std::stod(args.find("x")->second);
  std::cout << "x: " << x << std::endl; 
  double y = std::stod(args.find("y")->second);
  double height = std::stod(args.find("height")->second);
  double width = std::stod(args.find("width")->second);
  return std::make_unique<Box>(id, x, y, height, width);
}
