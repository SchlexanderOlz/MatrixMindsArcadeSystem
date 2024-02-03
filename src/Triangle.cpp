#include "Triangle.hpp"


using namespace matrix_minds;

std::pair<double, double> Triangle::getRangeAt(double x) const {
    std::pair<double, double> range;
    auto to_fill = &range.first; // This is done based on the knowledge that indexing the trianlge here can only ever yield two values. TODO: Check this again after doing right-angle edge case
    for (auto& line : this->_connections) {
        if ((x > line.first->x
            && x > line.second->x)
            || 
            (x < line.first->x
            && x < line.second->x)) continue;

        const double length = line.first->x - line.second->x;
        if (length == 0) return std::make_pair(line.first->y, line.second->y);

        const double height = line.first->y - line.second->y;
        if (height == 0) {
            *to_fill = 0.0;
            to_fill = &range.second;
            continue;
        }

        const double slope = height / length;

        const double value_at_position = (slope * (x - line.first->x)) + line.first->y;
        *to_fill = value_at_position;
        to_fill = &range.second;
    }
    return std::move(range);
}

std::pair<double, double> Triangle::getRange() const {
    double smallest, biggest = this->_vertices[0].x;
    for (const auto& vertice: this->_vertices) {
        if (vertice.x < smallest) smallest = vertice.x;
        if (vertice.x > biggest) biggest = vertice.x;
    }

    return std::make_pair(smallest, biggest);
}