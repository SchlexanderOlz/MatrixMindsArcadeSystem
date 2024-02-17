#ifndef TRIANGLE 
#define TRIANGLE

#include <iostream>
#include <led-matrix.h>
#include <memory>
#include <array>

#include "DisplayItem.hpp"
#include "GraphicsEngine.hpp"

using namespace rgb_matrix;

namespace matrix_minds {
    struct Position {
        double x;
        double y;
        Position(double x, double y) : x(x), y(y) {}
    };

    class Triangle : public DisplayItem {
    private:
        const std::array<std::pair<const Position*, const Position*>, 3> connections_;
        const std::array<Position, 3> vertices_;

        inline static std::array<std::pair<const Position*, const Position*>, 3> make_connections(const std::array<Position, 3>& vertices) {
            std::array<std::pair<const Position*, const Position*>, 3> connections;
            for (size_t i = 0; i < connections.size(); ++i) {
                connections[i] = std::make_pair(&vertices[i % vertices.size()], &vertices[(i + 1) % vertices.size()]);
            }
            return connections;
        } 

    public:
        Triangle(std::array<Position, 3> vertices, Color color) : DisplayItem(std::move(color)), connections_(make_connections(vertices)), vertices_(std::move(vertices)) {}
        std::pair<double, double> getRangeAt(double x) const override;
        std::pair<double, double> getRange() const override;
        void display(shared_ptr<GraphicsEngine> engine) const override;
        ~Triangle() override = default;
  };
}


#endif
