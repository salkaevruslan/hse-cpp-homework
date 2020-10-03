#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "BitStream.h"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory>

namespace Huffman {

class HuffmanTree final {
private:
    class Node final {
    public:
        Node(unsigned char symbol, size_t frequency);

        explicit Node(BitStream::BitReader &in);

        Node(std::unique_ptr<Node> left, std::unique_ptr<Node> right);

        Node &getLeftNode() const noexcept;

        Node &getRightNode() const noexcept;

        unsigned char getSymbol() const noexcept;

        size_t getFrequency() const noexcept;

        bool isLeaf() const noexcept;

        void writeNode(BitStream::BitWriter &out);

    private:
        size_t frequency_{};
        unsigned char symbol_{};
        std::unique_ptr<Node> left_, right_;
    };

public:
    explicit HuffmanTree(std::vector<std::pair<std::size_t, unsigned char>> &frequencies);

    explicit HuffmanTree(BitStream::BitReader &in);

    const std::vector<bool> &getSymbolCode(unsigned char symbol) const;


    void writeTree(BitStream::BitWriter &out) const;

    size_t getTreeSize() const noexcept;

    unsigned char getSymbol(BitStream::BitReader &in) const;

private:
    std::unique_ptr<Node> root_;
    size_t tree_size_{};
    std::vector<std::vector<bool >> codes_{256};

    static std::unique_ptr<Node> nextNode(std::queue<std::unique_ptr<HuffmanTree::Node>> &merged_nodes,
                                          const std::vector<std::pair<std::size_t, unsigned char>> &frequencies,
                                          size_t &freq_pos);

    void buildCodes(Node &node, std::vector<bool> &code_prefix);

};

class HuffmanException final : public std::logic_error {
public:
    explicit HuffmanException(const char *msg);
};
}

#endif //HUFFMAN_H
