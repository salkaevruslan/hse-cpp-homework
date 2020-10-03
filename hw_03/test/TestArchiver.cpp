#include "doctest.h"
#include "HuffmanArchiver.h"
#include <vector>
#include <random>
#include <sstream>

namespace TestArchiver {

TEST_CASE ("Frequencies count") {
    std::stringstream is;
    std::string s = "test";
    for (size_t i = 0; i < 4; ++i) {
        unsigned char byte = s[i];
        is.put(byte);
    }
    BitStream::BitReader in(is);
    auto frequencies = Archiver::countFrequencies(in);
    CHECK(frequencies.size() == 256);
    CHECK(frequencies['e'].first == 1);
    CHECK(frequencies['s'].first == 1);
    CHECK(frequencies['t'].first == 2);
    CHECK(frequencies['t'].second == 't');
    CHECK(frequencies['a'].first == 0);
}

TEST_CASE ("Binary encoding") {
    std::stringstream is;
    std::stringstream os;
    std::string s = "test";
    for (size_t i = 0; i < 4; ++i) {
        unsigned char byte = s[i];
        is.put(byte);
    }
    Archiver::HuffmanArchiver compressor(is, os);
    compressor.compress();
    BitStream::BitReader in(os);
    std::size_t symbol_number;
    in >> symbol_number;
    CHECK(symbol_number == 4);
    Huffman::HuffmanTree tmp_tree(in);
    in.readNextByte();
    unsigned char byte;
    in >> byte;
    CHECK(byte == 0b01011000);
}

TEST_CASE ("End to end, big random text") {
    std::stringstream is;
    std::stringstream tmp;
    std::stringstream os;
    std::mt19937 gen;
    for (size_t i = 0; i < 5 * 1024 * 1024; ++i) {
        unsigned char byte = 67 + gen() % 27;
        is.put(byte);
    }
    Archiver::HuffmanArchiver compressor(is, tmp);
    compressor.compress();
    Archiver::HuffmanArchiver extractor(tmp, os);
    extractor.extract();
    auto extractor_stats = extractor.getStats();
    auto compressor_stats = compressor.getStats();
    CHECK(compressor_stats.getInputSize() == extractor_stats.getOutputSize());
    CHECK(compressor_stats.getOutputSize() == extractor_stats.getInputSize());
    CHECK(compressor_stats.getExtraDataSize() == extractor_stats.getExtraDataSize());
    CHECK(compressor_stats.getInputSize() <
          extractor_stats.getOutputSize() + extractor_stats.getExtraDataSize());
    CHECK(compressor_stats.getInputSize() == 5 * 1024 * 1024);
    is.clear();
    is.seekg(0);
    for (size_t i = 0; i < 5 * 1024 * 1024; ++i) {
        CHECK(is.get() == os.get());
    }
}

TEST_CASE ("End to end, empty file") {
    std::stringstream is;
    std::stringstream tmp;
    std::stringstream os;
    Archiver::HuffmanArchiver compressor(is, tmp);
    compressor.compress();
    Archiver::HuffmanArchiver extractor(tmp, os);
    extractor.extract();
    auto extractor_stats = extractor.getStats();
    auto compressor_stats = compressor.getStats();
    CHECK(compressor_stats.getInputSize() == extractor_stats.getOutputSize());
    CHECK(compressor_stats.getOutputSize() == extractor_stats.getInputSize());
    CHECK(compressor_stats.getExtraDataSize() == extractor_stats.getExtraDataSize());
    CHECK(compressor_stats.getInputSize() == 0);
    CHECK(compressor_stats.getOutputSize() == 0);
}

TEST_CASE ("End to end, big random bytes") {
    std::stringstream is;
    std::stringstream tmp;
    std::stringstream os;
    std::mt19937 gen;
    for (size_t i = 0; i < 5 * 1024 * 1024; ++i) {
        unsigned char byte = gen() % 256;
        is.put(byte);
    }
    Archiver::HuffmanArchiver compressor(is, tmp);
    compressor.compress();
    Archiver::HuffmanArchiver extractor(tmp, os);
    extractor.extract();
    auto extractor_stats = extractor.getStats();
    auto compressor_stats = compressor.getStats();
    CHECK(compressor_stats.getInputSize() == extractor_stats.getOutputSize());
    CHECK(compressor_stats.getOutputSize() == extractor_stats.getInputSize());
    CHECK(compressor_stats.getExtraDataSize() == extractor_stats.getExtraDataSize());
    CHECK(compressor_stats.getInputSize() == 5 * 1024 * 1024);
    is.clear();
    is.seekg(0);
    for (size_t i = 0; i < 5 * 1024 * 1024; ++i) {
        CHECK(is.get() == os.get());
    }
}

}
