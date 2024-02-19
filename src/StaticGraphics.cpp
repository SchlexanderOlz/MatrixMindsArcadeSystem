#include "StaticGraphics.hpp"

using namespace matrix_minds;


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

