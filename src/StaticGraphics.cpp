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
  string id = args.find("id")->second;
  double x = std::stod(args.find("x")->second);
  double y = std::stod(args.find("y")->second);
  string content = args.find("content")->second;
  return std::make_unique<TextField>(id, x, y, content);
}

shared_ptr<FieldFactory> FieldTypes::get(const string &field_name) {
  auto factory_iter =
      std::find_if(FieldTypes::fields_.begin(), FieldTypes::fields_.end(),
                   [&field_name](const unique_ptr<FieldFactory> &factory) {
                     return factory->getIdentifier() == field_name;
                   });
  if (factory_iter == FieldTypes::fields_.end())
    throw runtime_error("Factory not found");
  return shared_ptr<FieldFactory>((*factory_iter).get());
}

void StaticGraphics::instanciateField(const string &field_name,
                                      const map<string, string> args) {
  FieldTypes::get(field_name)->build(std::move(args));
}

void StaticGraphics::display(shared_ptr<GraphicsEngine> engine) const {
  vector<const DisplayItem *> shape;
  // Look into concurrency here
  for (const auto &field : this->active_fields_) {
    field->apply(engine);
  }
}