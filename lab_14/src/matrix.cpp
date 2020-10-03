#include "matrix.h"
#include <cstddef>
#include <cstdlib>

MatrixException::MatrixException(Exception e) noexcept {
    switch (e) {
        case addWrongDimensions:
            msg = "ADD: dimensions do not match.\n";
            break;
        case mulWrongDimensions:
            msg = "MUL: #arg1.columns != #arg2.rows.\n";
            break;
        case badIndex:
            msg = "ACCESS: bad index.\n";
            break;
        case unableOpenFile:
            msg = "LOAD: unable to open file.\n";
            break;
        case invalidFormat:
            msg = "LOAD: invalid file format.\n";
            break;
        default:
            std::abort();
    }
}

const char *MatrixException::what() const noexcept {
    return msg;
}

Matrix::Matrix(int32_t rows, int32_t cols) : rows_(rows), cols_(cols) {
    data_.resize(rows_, std::vector<int32_t>(cols_, 0));
}

Matrix::Matrix(const Matrix &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_.resize(rows_, std::vector<int32_t>(cols_, 0));
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

int Matrix::get(std::size_t row, std::size_t col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw MatrixException(MatrixException::badIndex);
    return data_[row][col];
}

void Matrix::set(std::size_t row, std::size_t col, int32_t val) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw MatrixException(MatrixException::badIndex);
    data_[row][col] = val;
}

std::size_t Matrix::get_rows() const {
    return rows_;
}

std::size_t Matrix::get_cols() const {
    return cols_;
}

Matrix &Matrix::operator=(Matrix other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(data_, other.data_);
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    if (rows_ != other.get_rows() || cols_ != other.get_cols())
        throw MatrixException(MatrixException::addWrongDimensions);
    Matrix tmp(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            tmp.set(i, j, data_[i][j] + other.get(i, j));
        }
    }
    *this = tmp;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    if (cols_ != other.get_rows())
        throw MatrixException(MatrixException::mulWrongDimensions);
    size_t tmp_rows = rows_;
    size_t tmp_cols = other.get_cols();
    Matrix tmp(tmp_rows, tmp_cols);
    for (size_t i = 0; i < tmp_rows; ++i) {
        for (size_t j = 0; j < tmp_cols; ++j) {
            int32_t val = 0;
            for (size_t k = 0; k < cols_; k++) {
                val += data_[i][k] * other.get(k, j);
            }
            tmp.set(i, j, val);
        }
    }
    *this = tmp;
    return *this;
}


