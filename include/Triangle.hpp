#ifndef TRIANGLE 
#define TRIANGLE

#include <led-matrix.h>
#include <array>

using namespace rgb_matrix;

namespace matrix_minds {
    struct Position {
        double x;
        double y;
        Position(double x, double y) : x(x), y(y) {}
    };

    class Triangle {
    private:
        const std::array<std::pair<const Position*, const Position*>, 3> connections_;
        const std::array<Position, 3> vertices_;
        const Color color_;

        inline static std::array<std::pair<const Position*, const Position*>, 3> make_connections(const std::array<Position, 3>& vertices) {
            std::array<std::pair<const Position*, const Position*>, 3> connections;
            for (size_t i = 0; i < connections.size(); ++i) {
                connections[i] = std::make_pair(&vertices[i % vertices.size()], &vertices[(i + 1) % vertices.size()]);
            }
            return connections;
        } 

    public:
        Triangle(std::array<Position, 3> vertices, Color color) : connections_(make_connections(vertices)), vertices_(std::move(vertices)), color_(color) {}
        
        std::pair<double, double> getRangeAt(double x) const;
        inline Color getColor() const { return this->color_; }
        std::pair<double, double> getRange() const;
  };
}


#endif
