#include "bin_manip.h"
#include <iostream>
#include <cassert>
#include <cstring>

write_le_int32::write_le_int32(int32_t n) {
    assert(n >= 0);
    for (int i = 0; i < 4; ++i) {
        _bytes.push_back(n % 256);
        n /= 256;
    }
}

std::ostream &operator<<(std::ostream &os, const write_le_int32 wi32) {
    assert(os);
    return wi32.write(os);
}

std::ostream &write_le_int32::write(std::ostream &os) const {
    for (int i = 0; i < 4; ++i) {
        os.write(&_bytes[_bytes.size() - i - 1], sizeof(char));
        assert(!os.fail());
    }
    return os;
}

read_le_int32::read_le_int32(int32_t &n) : _n(&n) {}

std::istream &operator>>(std::istream &is, read_le_int32 ri32) {
    assert(is);
    return ri32.read(is);
}

std::istream &read_le_int32::read(std::istream &is) {
    char byte = 0;
    *_n = 0;
    for (int i = 0; i < 4; ++i) {
        is.read(&byte, sizeof(char));
        assert(!is.fail());
        *_n = 256 * (*_n);
        *_n += (256 + byte) % 256;
    }
    return is;
}

write_bool::write_bool(bool b) : _b(b) {}

std::ostream &operator<<(std::ostream &os, const write_bool wb) {
    assert(os);
    return wb.write(os);
}

std::ostream &write_bool::write(std::ostream &os) const {
    os.write((char *) &_b, sizeof(_b));
    assert(!os.fail());
    return os;
}

read_bool::read_bool(bool &b) : _b(&b) {}

std::istream &operator>>(std::istream &is, read_bool rb) {
    assert(is);
    return rb.read(is);
}

std::istream &read_bool::read(std::istream &is) {
    is.read((char *) _b, 1);
    return is;
}


write_c_str::write_c_str(const char *str) {
    assert(str);
    _str = str;
}

std::ostream &operator<<(std::ostream &os, const write_c_str ws) {
    assert(os);
    return ws.write(os);
}

std::ostream &write_c_str::write(std::ostream &os) const {
    assert(_str[strlen(_str)] == 0);
    os.write(_str, strlen(_str) + 1);
    assert(!os.fail());
    return os;
}

read_c_str::read_c_str(char *str, size_t length) : _length(length) {
    assert(str);
    _str = str;
}

std::istream &operator>>(std::istream &is, read_c_str rs) {
    assert(is);
    return rs.read(is);
}

std::istream &read_c_str::read(std::istream &is) {
    size_t current_length = 0;
    char c = 1;
    while (is.peek() != EOF) {
        assert(current_length <= _length);
        is.read(&c, 1);
        assert(!is.fail());
        _str[current_length] = c;
        ++current_length;
        if (c == 0)
            break;
    }
    assert(is.peek() != EOF);
    return is;
}

