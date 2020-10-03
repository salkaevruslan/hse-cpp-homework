#ifndef LAB11_BIN_MANIP_H_INCLUDED
#define LAB11_BIN_MANIP_H_INCLUDED

#include <fstream>
#include <vector>

class write_le_int32 final {
public:
    explicit write_le_int32(int32_t n);

    std::ostream &write(std::ostream &os) const;

private:
    std::vector<char> _bytes;
};

std::ostream &operator<<(std::ostream &os, write_le_int32 wi32);

class read_le_int32 final {
public:
    explicit read_le_int32(int32_t &n);

    std::istream &read(std::istream &is);

private:
    int32_t *_n;
};

std::istream &operator>>(std::istream &os, read_le_int32 ri32);

class write_bool final {
public:
    explicit write_bool(bool b);

    std::ostream &write(std::ostream &os) const;

private:
    bool _b;
};

std::ostream &operator<<(std::ostream &os, write_bool wb);

class read_bool final {
public:
    explicit read_bool(bool &b);

    std::istream &read(std::istream &is);

private:
    bool *_b;
};

std::istream &operator>>(std::istream &os, read_bool rb);

class write_c_str final {
public:
    explicit write_c_str(const char *str);


    std::ostream &write(std::ostream &os) const;

private:
    const char *_str;
};

std::ostream &operator<<(std::ostream &os, write_c_str ws);

class read_c_str final {
public:
    read_c_str(char *str, size_t length);

    std::istream &read(std::istream &is);

private:
    char *_str;
    size_t _length;
};

std::istream &operator>>(std::istream &os, read_c_str rs);

#endif

