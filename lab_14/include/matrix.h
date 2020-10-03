#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cstdint>

class MatrixException final {
public:

    enum Exception {
        addWrongDimensions,
        mulWrongDimensions,
        badIndex,
        invalidFormat,
        unableOpenFile
    };

    explicit MatrixException(Exception e) noexcept;

    const char *what() const noexcept;

private:
    const char *msg;

};


class Matrix final {
public:
    Matrix(int32_t rows, int32_t cols);

    Matrix(const Matrix &other);

    int get(std::size_t row, std::size_t col) const;

    void set(std::size_t row, std::size_t col, int32_t val);

    std::size_t get_rows() const;

    std::size_t get_cols() const;

    Matrix &operator=(Matrix other);

    Matrix &operator+=(const Matrix &other);

    Matrix &operator*=(const Matrix &other);


private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<std::vector<int32_t>> data_;

};


#endif
