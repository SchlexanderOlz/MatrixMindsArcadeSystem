#include "StaticGraphics.hpp"

using namespace matrix_minds;

void TextField::apply(shared_ptr<GraphicsEngine> engine) const {
  engine->render(this);
}

void Box::apply(shared_ptr<GraphicsEngine> engine) const {
  const double pxx1 = 1.0 / engine->getSizeX();
  const double pxy1 = 1.0 / engine->getSizeY();

  Rectangle line_1(this->x - (this->width / 2.0),
                   this->y - (this->height / 2.0), this->height, pxx1,
                   this->color);
  Rectangle line_2(this->x + (this->width / 2.0),
                   this->y - (this->height / 2.0), this->height, pxx1,
                   this->color);
  Rectangle line_3(this->x - (this->width / 2.0),
                   this->y - (this->height / 2.0), pxy1, this->width,
                   this->color);
  Rectangle line_4(this->x - (this->width / 2.0),
                   this->y + (this->height / 2.0), pxy1, this->width,
                   this->color);

  engine->render(&line_1);
  engine->render(&line_2);
  engine->render(&line_3);
  engine->render(&line_4);
}

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

FieldFactory* FieldTypes::get(const string &field_name) {
  auto factory_iter =
      std::find_if(FieldTypes::fields_.begin(), FieldTypes::fields_.end(),
                   [&field_name](const unique_ptr<FieldFactory> &factory) {
                     return factory != nullptr && factory->getIdentifier() == field_name;
                   });
  if (factory_iter == FieldTypes::fields_.end())
    throw runtime_error("Factory not found: " + field_name);
  return (*factory_iter).get();
}

void StaticGraphics::instanciateField(const string &field_name,
                                      const map<string, string> args) {
  this->active_fields_.emplace_back(FieldTypes::get(field_name)->build(std::move(args)));
}

void StaticGraphics::display(shared_ptr<GraphicsEngine> engine) const {
  // Look into concurrency here
  for (const unique_ptr<Field>& field : this->active_fields_) {
    field->apply(engine);
  }
}

void StaticGraphics::loadStructure(const StructureNode* node) {
  // Come back here for child-parent thematics and inheriting attributes
  try {
    this->active_fields_.emplace_back(FieldTypes::get(node->name)->build(node->attributes));
  } catch (const runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
  for (const unique_ptr<StructureNode>& child : node->children) {
    std::cout << "childname: " << child->name << endl;
    this->loadStructure(child.get());
  }
  std::cout << "done: " << node->name << endl;
}

vector<unique_ptr<FieldFactory>> FieldTypes::fields_ = []{
  vector<unique_ptr<FieldFactory>> data;
  data.emplace_back(std::make_unique<TextFieldFactory>());
  data.emplace_back(std::make_unique<BoxFieldFactory>());
  return std::move(data);
}();

