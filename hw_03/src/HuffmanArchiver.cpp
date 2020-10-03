#include "HuffmanArchiver.h"
#include "BitStream.h"
#include <iostream>
#include <memory>

namespace Archiver {

HuffmanArchiver::HuffmanArchiver(std::istream &in, std::ostream &out) : out_(out), in_(in) {
}

void HuffmanArchiver::compress() {
    frequencies_ = countFrequencies(in_);
    tree_ = std::make_unique<Huffman::HuffmanTree>(frequencies_);
    countInputSize();
    countCompressedSize();
    countExtraDataSize();
    out_ << stats_.getInputSize();
    tree_->writeTree(out_);
    out_.flushBuffer();
    while (true) {
        unsigned char symbol;
        try {
            in_ >> symbol;
        }
        catch (const std::ios_base::failure &error) {
            if (in_.eof()) {
                break;
            } else {
                throw;
            }
        }
        out_ << tree_->getSymbolCode(symbol);
    }
    out_.flushBuffer();
}

void HuffmanArchiver::extract() {
    size_t output_size;
    in_ >> output_size;
    stats_.setOutputSize(output_size);
    if (!output_size) {
        stats_.setExtraDataSize(sizeof(output_size));
        return;
    }
    tree_ = std::make_unique<Huffman::HuffmanTree>(in_);
    in_.readNextByte();
    stats_.setExtraDataSize(in_.tellg() - 1);
    for (size_t i = 0; i < output_size; ++i) {
        auto symbol = tree_->getSymbol(in_);
        out_ << symbol;
    }
    out_.flushBuffer();
    stats_.setInputSize(in_.tellg() - stats_.getExtraDataSize());
}


std::vector<std::pair<std::size_t, unsigned char>> countFrequencies(BitStream::BitReader &in) {
    std::vector<std::pair<std::size_t, unsigned char>> frequencies{256};
    while (true) {
        unsigned char symbol;
        try {
            in >> symbol;
        } catch (std::ios_base::failure &error) {
            if (in.eof()) {
                break;
            } else {
                throw;
            }
        }
        ++frequencies[symbol].first;
        frequencies[symbol].second = symbol;
    }
    in.rewindStream();
    return frequencies;
}

void HuffmanArchiver::countInputSize() {
    size_t size = 0;
    for (auto frequency:frequencies_) {
        size += frequency.first;
    }
    stats_.setInputSize(size);
}

void HuffmanArchiver::countCompressedSize() {
    size_t output_size = 0;
    for (auto &frequency : frequencies_) {
        output_size += frequency.first * tree_->getSymbolCode(frequency.second).size();
    }
    stats_.setOutputSize((output_size + 7) / 8);
}

void HuffmanArchiver::countExtraDataSize() {
    stats_.setExtraDataSize(frequencies_.size() + (tree_->getTreeSize() + 7) / 8 + sizeof(size_t));
}

ArchiverStats HuffmanArchiver::getStats() const noexcept {
    return stats_;
}

size_t ArchiverStats::getInputSize() const noexcept {
    return input_size_;
}

size_t ArchiverStats::getOutputSize() const noexcept {
    return output_size_;
}

size_t ArchiverStats::getExtraDataSize() const noexcept {
    return extra_data_size_;
}

void ArchiverStats::setInputSize(size_t size) noexcept {
    input_size_ = size;
}

void ArchiverStats::setOutputSize(size_t size) noexcept {
    output_size_ = size;
}

void ArchiverStats::setExtraDataSize(size_t size) noexcept {
    extra_data_size_ = size;
}


std::vector<std::pair<std::size_t, unsigned char>> HuffmanArchiver::getFrequencies() const noexcept {
    return frequencies_;
}

}