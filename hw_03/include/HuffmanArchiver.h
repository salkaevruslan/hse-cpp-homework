#ifndef HUFFMAN_ARCHIVER_H
#define HUFFMAN_ARCHIVER_H

#include "Huffman.h"
#include <string>
#include <queue>
#include <memory>
#include <vector>
#include <utility>
#include <fstream>

namespace Archiver {

class ArchiverStats final {
public:
    size_t getInputSize() const noexcept;

    size_t getOutputSize() const noexcept;

    size_t getExtraDataSize() const noexcept;

    void setInputSize(size_t size) noexcept;

    void setOutputSize(size_t size) noexcept;

    void setExtraDataSize(size_t size) noexcept;

private:
    size_t input_size_{};
    size_t output_size_{};
    size_t extra_data_size_{};
};

class HuffmanArchiver final {
public:
    HuffmanArchiver(std::istream &in, std::ostream &out);

    void compress();

    void extract();

    ArchiverStats getStats() const noexcept;

    std::vector<std::pair<std::size_t, unsigned char>> getFrequencies() const noexcept;

private:

    void countCompressedSize();

    void countExtraDataSize();

    void countInputSize();

private:
    std::vector<std::pair<std::size_t, unsigned char>> frequencies_{256};
    std::unique_ptr<Huffman::HuffmanTree> tree_{nullptr};
    BitStream::BitWriter out_;
    BitStream::BitReader in_;
    ArchiverStats stats_{};
};
std::vector<std::pair<std::size_t, unsigned char>> countFrequencies(BitStream::BitReader& in);

}

#endif //HUFFMAN_ARCHIVER_H
