#include "TextBuilder.hpp"

using namespace matrix_minds;

const CharacterNode* TextBuilder::builder_ = makeChefNode();

CharacterNode* makeChefNode() {
}


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
    this->nodes_.push_back(this->builder_->find(ch));
}

void TextBuilder::append(const char* str) {
    if (str == nullptr || *str == '\0') return;
    this->append(*str);
    this->append(++str);
}

Shape TextBuilder::build() const {
    Shape shape;
    for (const auto node : this->nodes_) {
        shape.emplace_back(std::move(node->getLines()));
    }
    return shape;
}