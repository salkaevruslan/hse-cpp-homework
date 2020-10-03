#include "doctest.h"
#include "BitStream.h"
#include <sstream>

namespace TestBitStream {

TEST_CASE ("Test bit read") {
    std::stringstream stream;
    stream.put(static_cast<unsigned char>(128));
    BitStream::BitReader in(stream);
    bool bit;
    in >> bit;
    CHECK(bit);
    in >> bit;
    CHECK(!bit);
}

TEST_CASE ("Test bit write") {
    std::stringstream stream;
    BitStream::BitWriter out(stream);
    out << true;
    out << false;
    out.flushBuffer();
    unsigned char byte = stream.get();
    CHECK(byte == 0b10000000);
}

TEST_CASE ("End to end write and read") {
    std::stringstream stream;
    BitStream::BitWriter out(stream);
    out << 12345;
    out.flushBuffer();
    BitStream::BitReader in(stream);
    unsigned int output;
    in >> output;
    CHECK(output == 12345);
}

}