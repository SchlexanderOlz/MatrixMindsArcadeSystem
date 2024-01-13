#include "apps/Printer.hpp"

using namespace matrix_minds;

void Printer::run() {
    for (;;) {
        this->performAction(this->controler_->getAction());
    }
}

void Printer::performAction(const Action action) {
    switch (action) {
        case Action::Left:
            this->builder_.append('H');
            this->engine_->render(this->builder_.build());
            this->engine_->show();
            this->builder_.clear();
    };
}
