#include "DisplayItem.hpp"

using namespace matrix_minds;

void DisplayItem::display(shared_ptr<GraphicsEngine> engine) const {
    engine->render(this);
}