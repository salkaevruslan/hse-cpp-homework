#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>

static constexpr int32_t REG_NUMBER = 10;

class read_register final {
public:
    explicit read_register(int &reg);

    std::istream &read(std::istream &is);

private:
    int32_t *reg_;
};

read_register::read_register(int32_t &reg) : reg_(&reg) {
}

std::istream &read_register::read(std::istream &is) {
    std::string s;
    is >> s;
    *reg_ = std::stoi(s.substr(1, s.length() - 1));
    return is;
}

std::istream &operator>>(std::istream &is, read_register rr) {
    return rr.read(is);
}

class read_value final {
public:
    explicit read_value(int32_t &val);

    std::istream &read(std::istream &is);

private:
    int32_t *val_;
};

read_value::read_value(int32_t &val) : val_(&val) {
}

std::istream &read_value::read(std::istream &is) {
    if (is.eof() || is.peek() == EOF)
        throw MatrixException(MatrixException::invalidFormat);
    try{
    is >> *val_;
    }catch(const std::ios_base::failure &ex){
        throw MatrixException(MatrixException::invalidFormat);
    }
    return is;
}

std::istream &operator>>(std::istream &is, read_value rv) {
    return rv.read(is);
}


Matrix load(std::string filename) {
    std::ifstream is;
    is.open(filename);
    if (is.fail())
        throw MatrixException(MatrixException::unableOpenFile);
    int32_t rows, cols;
    is.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    is >> read_value(rows) >> read_value(cols);
    std::vector<std::vector<int32_t>> tmp_data(rows, std::vector<int32_t>(cols, 0));
    for (size_t i = 0; i < (size_t) rows; ++i) {
        for (size_t j = 0; j < (size_t) cols; ++j) {
            is >> read_value(tmp_data[i][j]);
        }
    }
    Matrix tmp = Matrix(rows, cols);
    for (size_t i = 0; i < (size_t) rows; ++i) {
        for (size_t j = 0; j < (size_t) cols; ++j) {
            tmp.set(i, j, tmp_data[i][j]);
        }
    }
    return tmp;
}

void print(Matrix &matrix) {
    for (size_t i = 0; i < matrix.get_rows(); ++i) {
        for (size_t j = 0; j < matrix.get_cols(); ++j) {
            std::cout << matrix.get(i, j) << ' ';
        }
        std::cout << '\n';
    }
}

void add(Matrix &matrix1, const Matrix matrix2) {
    matrix1 += matrix2;
}

void mul(Matrix &matrix1, const Matrix matrix2) {
    matrix1 *= matrix2;
}

void elem(int row, int col, Matrix &matrix) {
    std::cout << matrix.get(row, col) << '\n';
}

int main() {
    std::string s;
    std::vector<Matrix> registers(REG_NUMBER, Matrix(0, 0));
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    std::cout.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    while (true) {
        try{
            std::cin >> s;
        } catch(const std::ios_base::failure &ex) {
            break;
        }
        try {
            if (s == "load") {
                int reg;
                std::string filename;
                std::cin >> read_register(reg) >> filename;
                Matrix tmp = registers[reg];
                registers[reg] = load(filename);
                continue;
            }
            if (s == "print") {
                int reg;
                std::cin >> read_register(reg);
                print(registers[reg]);
                continue;
            }
            if (s == "add") {
                int reg1, reg2;
                std::cin >> read_register(reg1) >> read_register(reg2);
                add(registers[reg1], registers[reg2]);
                continue;
            }
            if (s == "mul") {
                int reg1, reg2;
                std::cin >> read_register(reg1) >> read_register(reg2);
                mul(registers[reg1], registers[reg2]);
                continue;
            }
            if (s == "elem") {
                int row, col, reg;
                std::cin >> read_register(reg) >> row >> col;
                elem(row, col, registers[reg]);
                continue;
            }
            if (s == "exit") {
                break;
            }
        } catch (const MatrixException &ex) {
            std::cout << ex.what();
        } catch (const std::bad_alloc &ex) {
            std::cout << "Unable to allocate memory.\n";
        } catch (const std::ios_base::failure &ex) {
            std::cout << ex.what();
        }
    }
    return 0;
}
