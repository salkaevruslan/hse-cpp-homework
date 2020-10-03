#include "doctest.h"
#include "Huffman.h"
#include <sstream>
#include <vector>

namespace TestHuffman {

TEST_CASE ("Binary tree from frequencies") {
    std::vector<std::pair<std::size_t, unsigned char>> frequencies = {
            {1, 'e'},
            {1, 's'},
            {2, 't'}
    };
    Huffman::HuffmanTree tree(frequencies);
    std::vector<bool> code;
    code = tree.getSymbolCode('t');
    CHECK(code.size() == 1);
    code = tree.getSymbolCode('e');
    CHECK(code.size() == 2);
    code = tree.getSymbolCode('s');
    CHECK(code.size() == 2);
    CHECK_THROWS_WITH(tree.getSymbolCode('a'), "Bad symbol");
}

TEST_CASE ("Write binary tree") {
    std::vector<std::pair<std::size_t, unsigned char>> frequencies = {
            {1, static_cast<unsigned char >(1)},
            {1, static_cast<unsigned char >(2)},
            {2, static_cast<unsigned char >(0)}
    };
    Huffman::HuffmanTree tree(frequencies);
    std::stringstream stream;
    BitStream::BitWriter writer(stream);
    tree.writeTree(writer);
    writer.flushBuffer();
    BitStream::BitReader in(stream);
    unsigned char byte;
    in >> byte;
    CHECK(byte == 0b01000000);
    in >> byte;
    CHECK(byte == 0b00010000);
    in >> byte;
    CHECK(byte == 0b00011000);
    in >> byte;
    CHECK(byte == 0b00010000);
}

TEST_CASE ("Binary tree from stream") {
    std::stringstream stream;
    stream.put(0b01000000);
    stream.put(0b00010000);
    stream.put(0b00011000);
    stream.put(0b00010000);
    std::vector<bool> code;
    BitStream::BitReader in(stream);
    Huffman::HuffmanTree tree(in);
    code = tree.getSymbolCode(static_cast<unsigned char>(0));
    CHECK(code.size() == 1);
    CHECK(code[0] == 0);
    code = tree.getSymbolCode(static_cast<unsigned char>(1));
    CHECK(code.size() == 2);
    CHECK(code[0] == 1);
    CHECK(code[1] == 0);
    code = tree.getSymbolCode(static_cast<unsigned char>(2));
    CHECK(code.size() == 2);
    CHECK(code[0] == 1);
    CHECK(code[1] == 1);
    CHECK_THROWS_WITH(tree.getSymbolCode('a'), "Bad symbol");
}

}
