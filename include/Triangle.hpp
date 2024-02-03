#ifndef TRIANGLE 
#define TRIANGLE

#include <led-matrix.h>
#include <array>

using namespace rgb_matrix;

namespace matrix_minds {
    struct Position {
        double x;
        double y;
    };

    class Triangle {
    private:
        const std::array<std::pair<const Position*, const Position*>, 3> _connections;
        const std::array<Position, 3> _vertices;
        const Color _color;


        inline static std::array<std::pair<const Position*, const Position*>, 3> make_connections(const std::array<Position, 3>& vertices) {
            std::array<std::pair<const Position*, const Position*>, 3> connections;
            for (size_t i = 0; i < connections.size(); ++i) {
                connections[i] = std::make_pair(&vertices[i % vertices.size()], &vertices[(i + 1) % vertices.size()]);
            }
            return std::move(connections);
        } 

    public:
        Triangle(std::array<Position, 3> vertices, Color color) : _connections(make_connections(vertices)), _vertices(std::move(vertices)), _color(color) {}
        
        std::pair<double, double> getRangeAt(double x) const;
        inline Color getColor() const { return this->_color; }
        std::pair<double, double> getRange() const;
  };
}


#endif
