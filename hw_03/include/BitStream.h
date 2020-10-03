#ifndef BIT_STREAM_H_
#define BIT_STREAM_H_

#include <string>
#include <fstream>
#include <vector>
#include <climits>
#include <cassert>

namespace BitStream {

class BitReader final {
public:
    explicit BitReader(std::istream &in);

    BitReader &operator>>(bool &bit);

    template<typename T>
    BitReader &operator>>(T &val);

    void readNextByte();

    size_t tellg();

    void rewindStream();

    bool eof() const;

private:
    unsigned char buffer_;
    std::istream &in_;
    std::size_t pos_;
};

class BitWriter final {
public:
    explicit BitWriter(std::ostream &out);

    BitWriter &operator<<(bool bit);

    BitWriter &operator<<(const std::vector<bool> &bits);

    template<typename T>
    BitWriter &operator<<(const T &val);

    void flushBuffer();

private:
    unsigned char buffer_;
    std::ostream &out_;
    std::size_t pos_;
};

template<typename T>
BitReader &BitReader::operator>>(T &val) {
    std::size_t size = sizeof(T) * CHAR_BIT;
    T tmp_value = 0;
    for (std::size_t i = 0; i < size; i++) {
        bool bit;
        *this >> bit;
        tmp_value |= (bit << (size - 1 - i));
    }
    val = tmp_value;
    return *this;
}

template<typename T>
BitWriter &BitWriter::operator<<(const T &val) {
    std::size_t size = sizeof(T) * CHAR_BIT;
    for (std::size_t i = 0; i < size; i++) {
        *this << static_cast<bool>(val & (1 << (size - i - 1)));
    }
    return *this;
}
}

#endif //BIT_STREAM_H_