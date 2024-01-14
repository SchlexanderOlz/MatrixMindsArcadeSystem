#include "TextBuilder.hpp"

using namespace matrix_minds;

static CharacterNode* makeChefNode() {
    // Call method of the textbuilder which constructs this bs
    RectangularArea line1(-1.0, -1.0, 2.0, 0.1, Color(255, 255, 255));
    RectangularArea line2(0.85, -1.0, 2.0, 0.1, Color(255, 255, 255));
    RectangularArea line3(-1.0, 0.0, 0.1, 2.0, Color(255, 255, 255));

    return new CharacterNode('H', { line1, line2, line3 });
}

const CharacterNode* TextBuilder::builder_ = makeChefNode();


Shape CharacterNode::getLines(const char ch) const {
    if (this->ch_ == ch) {
        return this->shape_;
    }
    return this->left_->ch_ < ch ? this->left_->getLines(ch) : this->right_->getLines(ch);
}

void CharacterNode::insert(const char ch, const Shape shape) {
    if (this->ch_ < ch) {
        if (this->right_ != nullptr) return this->right_->insert(ch, std::move(shape));
        this->right_ = new CharacterNode(ch, std::move(shape));
    }

    if (this->left_ != nullptr) return this->left_->insert(ch, std::move(shape));
    this->left_ = new CharacterNode(ch, std::move(shape));
}

const CharacterNode* CharacterNode::find(const char ch) const {
    if (this->ch_ == ch) {
        return this;
    }
    return this->left_->ch_ < ch ? this->left_->find(ch) : this->right_->find(ch);
}

void TextBuilder::append(const char ch) {
    auto fund = this->builder_->find(ch);
    this->nodes_.push_back(fund);
}

void TextBuilder::append(const char* str) {
    if (str == nullptr || *str == '\0') return;
    this->append(*str);
    this->append(++str);
}

Shape TextBuilder::build() const {
    Shape shape;
    for (const auto node : this->nodes_) {
        // TODO: There has to be a different way to concatenate these two vectors without iterating over them
        for (auto line : node->getLines()) {
            shape.emplace_back(std::move(line));
        }
    }
    return shape;
}
