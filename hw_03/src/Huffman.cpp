#include "Huffman.h"
#include <cassert>

namespace Huffman {

HuffmanTree::Node::Node(unsigned char symbol, size_t frequency) : frequency_(frequency),
                                                                  symbol_(symbol) {
}

HuffmanTree::Node::Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right) : frequency_(left->frequency_ +
                                                                                              right->frequency_),
                                                                                   left_(std::move(left)),
                                                                                   right_(std::move(right)) {
}

HuffmanTree::Node::Node(BitStream::BitReader &in) {
    bool is_leaf;
    in >> is_leaf;
    if (is_leaf) {
        left_ = nullptr;
        right_ = nullptr;
        in >> symbol_;
    } else {
        left_ = std::make_unique<Node>(in);
        right_ = std::make_unique<Node>(in);
        if (!left_ || !right_) {
            throw std::bad_alloc();
        }
    }
}

unsigned char HuffmanTree::Node::getSymbol() const noexcept {
    return symbol_;
}

size_t HuffmanTree::Node::getFrequency() const noexcept {
    return frequency_;
}

bool HuffmanTree::Node::isLeaf() const noexcept {
    return !left_ && !right_;
}

void HuffmanTree::Node::writeNode(BitStream::BitWriter &out) {
    out << isLeaf();
    if (isLeaf()) {
        out << symbol_;
    } else {
        left_->writeNode(out);
        right_->writeNode(out);
    }
}

HuffmanTree::Node &HuffmanTree::Node::getLeftNode() const noexcept {
    return *left_;
}

HuffmanTree::Node &HuffmanTree::Node::getRightNode() const noexcept {
    return *right_;
}

const std::vector<bool> &HuffmanTree::getSymbolCode(unsigned char symbol) const {
    if (codes_[symbol].empty())
        throw HuffmanException("Bad symbol");
    return codes_[symbol];
}

HuffmanTree::HuffmanTree(std::vector<std::pair<std::size_t, unsigned char>> &frequencies) {
    auto elementZeroFrequency = [](std::pair<size_t, unsigned char> x) { return !x.first; };
    std::sort(frequencies.begin(), frequencies.end());
    frequencies.resize(std::remove_if(frequencies.begin(), frequencies.end(),
                                      elementZeroFrequency) - frequencies.begin());
    if (frequencies.empty()) {
        root_ = nullptr;
        return;
    }
    std::queue<std::unique_ptr<Node>> merged_nodes;
    std::size_t freq_pos = 0;
    while (merged_nodes.size() + frequencies.size() - freq_pos > 1) {
        auto left = nextNode(merged_nodes, frequencies, freq_pos);
        auto right = nextNode(merged_nodes, frequencies, freq_pos);
        merged_nodes.push(std::make_unique<Node>(std::move(left), std::move(right)));
    }
    std::unique_ptr<Node> tmp(nextNode(merged_nodes, frequencies, freq_pos));
    root_ = std::move(tmp);
    std::vector<bool> code_prefix;
    buildCodes(*root_, code_prefix);
}


HuffmanTree::HuffmanTree(BitStream::BitReader &in) : root_(std::make_unique<Node>(in)) {
    std::vector<bool> code_prefix;
    buildCodes(*root_, code_prefix);
}

void HuffmanTree::buildCodes(Node &node, std::vector<bool> &code_prefix) {
    ++tree_size_;
    if (node.isLeaf()) {
        codes_[node.getSymbol()] = (&node == root_.get() ? std::vector<bool>(1) : code_prefix);
        return;
    }
    code_prefix.push_back(false);
    buildCodes(node.getLeftNode(), code_prefix);
    code_prefix.pop_back();
    code_prefix.push_back(true);
    buildCodes(node.getRightNode(), code_prefix);
    code_prefix.pop_back();
}

void HuffmanTree::writeTree(BitStream::BitWriter &out) const {
    if (!root_)
        return;
    root_->writeNode(out);
}

size_t HuffmanTree::getTreeSize() const noexcept {
    return tree_size_;
}

unsigned char HuffmanTree::getSymbol(BitStream::BitReader &in) const {
    Node *node = root_.get();
    while (!node->isLeaf()) {
        bool direction;
        in >> direction;
        if (direction) {
            node = &node->getRightNode();
        } else {
            node = &node->getLeftNode();
        }
    }
    return node->getSymbol();
}

std::unique_ptr<HuffmanTree::Node>
HuffmanTree::nextNode(std::queue<std::unique_ptr<HuffmanTree::Node>> &merged_nodes,
                      const std::vector<std::pair<std::size_t, unsigned char>> &frequencies,
                      size_t &freq_pos) {
    if (merged_nodes.empty() && freq_pos < frequencies.size()) {
        auto frequency = frequencies[freq_pos++];
        return std::make_unique<HuffmanTree::Node>(frequency.second, frequency.first);
    }
    if (!merged_nodes.empty() && freq_pos >= frequencies.size()) {
        auto node = std::move(merged_nodes.front());
        merged_nodes.pop();
        return node;
    }
    if (!merged_nodes.empty() && freq_pos < frequencies.size()) {
        if (merged_nodes.front()->getFrequency() < frequencies[freq_pos].first) {
            auto node = std::move(merged_nodes.front());
            merged_nodes.pop();
            return node;
        } else {
            auto frequency = frequencies[freq_pos++];
            return std::make_unique<HuffmanTree::Node>(frequency.second, frequency.first);
        }
    }
    assert(false);
}

HuffmanException::HuffmanException(const char *msg) : logic_error(msg) {
}

}
