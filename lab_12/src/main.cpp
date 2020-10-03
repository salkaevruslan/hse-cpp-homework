#include "my_vector.h"
#include "my_vector_test.h"
#include <iostream>
#include <cstring>

namespace product {

    class Product final {
    public:
        Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price) {
            name_ = new char[strlen(name) + 1];
            std::strcpy(name_, name);
        }

        Product(const Product &other) : Product{other.name_, other.quantity_, other.price_} {
        }

        Product(Product &&other) noexcept: quantity_(other.quantity_), price_(other.price_) {
            name_ = other.name_;
            other.name_ = nullptr;
        }

        Product &operator=(const Product &other) {
            Product tmp(other);
            swap(tmp);
            return *this;
        }

        Product &operator=(Product &&other) noexcept {
            swap(other);
            return *this;
        }

        ~Product() {
            delete[] name_;
        }

        std::ostream &write(std::ostream &os) {
            os << "Product: " << name_ << " " << quantity_ << " " << price_;
            return os;
        }

    private:
        char *name_;  // Указатель владеет C-style строкой, на которую указывает.
        int quantity_;
        double price_;

        void swap(Product &other) noexcept {
            Product tmp = std::move(other);
            other = std::move(*this);
            *this = std::move(other);
        }
    };

    std::ostream &operator<<(std::ostream &os, Product p) {
        return p.write(os);
    }

}  // namespace product


int main() {
    test::my_vector_test<int> test1(5, 10);
    test::my_vector_test<product::Product> test2(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    test1.run_tests();
    test1.run_default_constructible_tests();
    test2.run_tests();
    test::Test::showFinalResult();
    return 0;
}
