#include "../include/Menu.hpp"

using namespace matrix_minds;

void Menu::run() {
  for (;;) {
    this->performAction(this->controler_->getAction());
  }
}

void Menu::performAction(const Action action) {
  switch (action) {
    case Action::Right:
      this->focused_app_idx++;
    case Action::Left:
      std::min(this->focused_app_idx--, this->apps.size());
    case Action::Confirm:
      this->apps[this->focused_app_idx].first->buildApp()->run();
    default:
      return;
  }
  this->drawState();
}

void Menu::drawState() {
  // This is missing a focused display of the element currently in focus
  constexpr float ml = 0.1;
  constexpr float mt = 0.1;
  constexpr float mb = 0.05;

  constexpr uint8_t items = 3;
  constexpr float scale = 0.2;

  for (size_t i = 0; i < this->apps.size(); i++) {
    // TODO: Multi-thread this when possible
    for (const shared_ptr<DisplayItem> line : this->apps[i].second) {
      /* const float x = line->getPosX() * scale + ml + ((1.0 - ml) / items) * (i % items);
      const float y = line->getPosY() * scale + (i / items) * (scale + mb);
      const float height = line->getHeight() * scale;
      const float size = line->getRangeAt()
      const float width = line->getWidth() * scale;

      // TODO: Handle overflow of apps here
      Rectangle new_line(x, y, height, width, line->getColor());
      this->engine_->render(&new_line); */
      this->engine_->render(line.get());
    }
  }
}
