#include "BitStream.h"
#include <iostream>

namespace BitStream {

BitReader::BitReader(std::istream &in) : in_(in) {
    if (!in_) {
        throw std::ios_base::failure("Can't open input stream");
    }
    in_.exceptions(std::ios_base::eofbit | std::ios_base::badbit);
    buffer_ = 0;
    pos_ = CHAR_BIT;
}

BitReader &BitReader::operator>>(bool &bit) {
    if (pos_ >= CHAR_BIT) {
        readNextByte();
    }
    bit = buffer_ & (1 << (CHAR_BIT - pos_++ - 1));
    return *this;
}

void BitReader::readNextByte() {
    unsigned char tmp_buffer = in_.get();
    pos_ = 0;
    buffer_ = tmp_buffer;
}


size_t BitReader::tellg() {
    return in_.tellg();
}

void BitReader::rewindStream() {
    in_.clear();
    in_.seekg(0);
    buffer_ = 0;
    pos_ = CHAR_BIT;
}

bool BitReader::eof() const {
    return in_.eof();
}


BitWriter::BitWriter(std::ostream &out) : out_(out) {
    if (!out_) {
        throw std::ios_base::failure("Can't open output stream");
    }
    out_.exceptions(std::ios_base::eofbit | std::ios_base::badbit);
    pos_ = 0;
    buffer_ = 0;
}

BitWriter &BitWriter::operator<<(bool bit) {
    if (pos_ >= CHAR_BIT) {
        flushBuffer();
    }
    buffer_ |= (bit << (CHAR_BIT - 1 - pos_++));
    return *this;
}

BitWriter &BitWriter::operator<<(const std::vector<bool> &bits) {
    for (bool bit : bits) {
        *this << bit;
    }
    return *this;
}

void BitWriter::flushBuffer() {
    if (pos_) {
        out_.put(buffer_);
    }
    pos_ = 0;
    buffer_ = 0;
}

}