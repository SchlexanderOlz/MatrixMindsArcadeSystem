#include "Triangle.hpp"


using namespace matrix_minds;

std::pair<double, double> Triangle::getRangeAt(double x) const {
    constexpr double epsilon = 1e-10; // TODO: Move this in some global file

    std::pair<double, double> range;
    auto to_fill = &range.first; // This is done based on the knowledge that indexing the trianlge here can only ever yield two values. TODO: Check this again after doing right-angle edge case
    for (const auto& line : this->connections_) {
        if ((x > line.first->x
            && x > line.second->x)
            || 
            (x < line.first->x
            && x < line.second->x)) continue;

        const Position* begin = line.first;
        const Position* end = line.second;

        if (line.second->x < line.first->x) {
            begin = line.second;
            end = line.first;
        }

        const double length = end->x - begin->x;
        if (std::abs(length) < epsilon) {
            if (std::abs(end->x - x) < epsilon) return std::make_pair(begin->y, end->y);
            else continue;
        }

        const double height = end->y - begin->y;
        if (std::abs(height) < epsilon) {
            *to_fill = end->y;
            to_fill = &range.second;
            continue;
        }

        const double slope = height / length;

        const double value_at_position = (slope * std::abs(x - begin->x)) + begin->y;
        *to_fill = value_at_position;
        to_fill = &range.second;
    }
    std::cout << "Made it1: " << range.first << std::endl;
    std::cout << "Made it2: " << range.second << std::endl;
    return range;
}

std::pair<double, double> Triangle::getRange() const {
    double smallest, biggest;
    smallest = biggest = this->vertices_[0].x;
    for (const auto& vertex: this->vertices_) {
        if (vertex.x < smallest) smallest = vertex.x;
        if (vertex.x > biggest) biggest = vertex.x;
    }
    return std::make_pair(smallest, biggest);
}

void Triangle::display(shared_ptr<GraphicsEngine> engine) const {
    engine->render(this);
}