#include "../include/Menu.hpp"

using namespace matrix_minds;

void Menu::render() {
  constexpr float ml = 0.1;
  constexpr float mt = 0.1;
  constexpr float mb = 0.05;

  constexpr uint8_t items = 3;
  constexpr float scale = 0.2;

  for (size_t i = 0; i < apps.size(); i++) {
    // TODO: Multi-thread this when possible
    for (const Line line : apps[i].getIcon()) {
      const float x = line.getPosX() * scale + ml + ((1.0 - ml) / items) * (i % items);
      const float y = line.getPosY() * scale + (i / items) * (scale + mb);
      const float height = line.getHeight() * scale;
      const float width = line.getWidth() * scale;

      // TODO: Handle overflow of apps here
      Line new_line(x, y, height, width, line.getColor());
      this->engine->render(new_line);
    }
  }
}
