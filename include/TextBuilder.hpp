#ifndef TEXT_BUILDER
#define TEXT_BUILDER

#include <iostream>
#include <memory>
#include <pugixml.hpp>

#include "RectangularArea.hpp"

using namespace std;

namespace matrix_minds
{
  class CharacterNode {
    private:
      const char ch_;
      CharacterNode* left_;
      CharacterNode* right_;
      const Shape shape_;

    public:
      CharacterNode(char ch, Shape shape) : ch_(ch), shape_(shape) {}
      /**
       * @brief Continiously calls other node members until a node has the requested value.
       * Values on the left side of the node are smaller whiler those on the right side are greater or equal
      */
      inline Shape getLines() const { return this->shape_; }
      Shape getLines(const char ch) const;
      void insert(const char ch, const Shape shape);

      const CharacterNode* find(const char ch) const;
  };

  class TextBuilder
  {
  private:
    vector<const CharacterNode*> nodes_;
    static const CharacterNode* builder_;

  public:
    Shape build() const;
    void append(const char ch);
    void append(const char* str);
    inline void clear() { this->nodes_.clear(); }
    void remove();
    void remove(size_t pos);
    void remove(size_t begin, size_t end);
  };

}

#endif
