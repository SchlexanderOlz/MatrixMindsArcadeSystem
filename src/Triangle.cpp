#include "Triangle.hpp"


using namespace matrix_minds;

#include <iostream>
std::pair<double, double> Triangle::getRangeAt(double x) const {
    constexpr double epsilon = 1e-4; // TODO: Move this in some global file

    std::pair<double, double> range;
    auto to_fill = &range.first; // This is done based on the knowledge that indexing the trianlge here can only ever yield two values. TODO: Check this again after doing right-angle edge case
    for (auto& line : this->connections_) {
        std::cout << "Point 1: " << line.first->y << std::endl;
        std::cout << "Point 2: " << line.second->y << std::endl;
        if ((x > line.first->x
            && x > line.second->x)
            || 
            (x < line.first->x
            && x < line.second->x)) continue;

        const double length = std::abs(line.first->x - line.second->x);
        if (length < epsilon) return std::make_pair(line.first->y, line.second->y);

        const double height = std::abs(line.first->y - line.second->y);
        if (height < epsilon) {
            *to_fill = 0.0;
            to_fill = &range.second;
            continue;
        }

        const double slope = height / length;

        const double value_at_position = (slope * (x - line.first->x)) + line.first->y;
        *to_fill = value_at_position;
        to_fill = &range.second;
    }
    std::cout << "Made it1: " << range.first << std::endl;
    std::cout << "Made it2: " << range.second << std::endl;
    return std::move(range);
}

std::pair<double, double> Triangle::getRange() const {
    double smallest, biggest;
    smallest = biggest = this->vertices_[0].x;
    for (const auto& vertice: this->vertices_) {
        if (vertice.x < smallest) smallest = vertice.x;
        if (vertice.x > biggest) biggest = vertice.x;
    }
    return std::make_pair(smallest, biggest);
}