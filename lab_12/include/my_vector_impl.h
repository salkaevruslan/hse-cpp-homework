#ifndef MY_VECTOR_IMPL_H
#define MY_VECTOR_IMPL_H

#include "my_vector.h"
#include <cstdio>
#include <cstdlib>
#include <memory>

namespace my_vector {

    template<typename T>
    my_vector<T>::my_vector() noexcept :size_(0), capacity_(0), array_(nullptr) {}

    template<typename T>
    my_vector<T>::my_vector(std::size_t n): my_vector{} {
        reserve(n);
        for (std::size_t i = 0; i < n; ++i) {
            push_back(T());
        }
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector <T> &other): my_vector<T>{} {
        my_vector<T> tmp = allocate_vector(other.capacity_);
        for (size_t i = 0; i < other.size_; i++) {
            tmp.push_back(other[i]);
        }
        *this = std::move(tmp);
    }

    template<typename T>
    my_vector<T>::my_vector(my_vector <T> &&other) noexcept :size_(other.size_), capacity_(other.capacity_),
                                                             array_(other.array_) {
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    template<typename T>
    my_vector <T> &my_vector<T>::operator=(const my_vector <T> &other) {
        if (&other == this)
            return *this;
        my_vector<T> tmp(other);
        swap(tmp);
        return *this;
    }

    template<typename T>
    my_vector <T> &my_vector<T>::operator=(my_vector <T> &&other) noexcept {
        if (&other == this)
            return *this;
        swap(other);
        return *this;
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        destruct_array();
        delete[] reinterpret_cast<char *>(array_);
    }

    template<typename T>
    std::size_t my_vector<T>::size() const noexcept {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const noexcept {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const noexcept {
        return size_ == 0;
    }

    template<typename T>
    void my_vector<T>::reserve(size_t n) {
        if (n <= capacity_)
            return;
        my_vector<T> tmp = allocate_vector(n);
        for (size_t i = 0; i < size_; i++) {
            tmp.push_back(std::move(array_[i]));
        }
        *this = std::move(tmp);
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        if (n <= size_) {
            for (std::size_t i = size_ - 1; i >= n; --i) {
                array_[i].~T();
            }
            size_ = n;
            return;
        } else {
            my_vector<T> tmp = allocate_vector(n);
            try {
                for (std::size_t i = size_; i < n; ++i) {
                    new(tmp.array_ + i) T();
                }
            } catch (...) {
                for (std::size_t i = size_; i < n; ++i) {
                    tmp[i].~T();
                }
                throw;
            }
            for (std::size_t i = 0; i < size_; ++i) {
                new(tmp.array_ + i) T(std::move(array_[i]));
            }
            tmp.size_ = n;
            *this = std::move(tmp);
        }
    }

    template<typename T>
    T &my_vector<T>::operator[](std::size_t index) {
        if (index >= size_)
            throw std::range_error("Out of range");
        return array_[index];
    }

    template<typename T>
    const T &my_vector<T>::operator[](std::size_t index) const {
        if (index >= size_)
            throw std::range_error("Out of range");
        return array_[index];
    }

    template<typename T>
    void my_vector<T>::push_back(const T &t) {
        push_back(T{t});
    }

    template<typename T>
    void my_vector<T>::push_back(T &&t) {
        reserve(size_ + 1);
        new(array_ + size_) T(std::move(t));
        ++size_;
    }

    template<typename T>
    void my_vector<T>::pop_back() {
        if (size_ == 0)
            throw std::logic_error("Can't pop back from empty vector.");
        array_[size_ - 1].~T();
        size_--;
    }

    template<typename T>
    void my_vector<T>::clear() noexcept {
        destruct_array();
        size_ = 0;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const my_vector <T> &v) {
        for (std::size_t i = 0; i < v.size() - 1; i++) {
            os << v[i] << " ";
        }
        if (!v.empty())
            os << v[v.size() - 1];
        return os;
    }

    template<typename T>
    my_vector <T> my_vector<T>::allocate_vector(std::size_t capacity) {
        capacity = ceil_power_of_two(capacity);
        my_vector<T> result;
        result.array_ = reinterpret_cast<T *>(new char[sizeof(T) * capacity]);
        result.capacity_ = capacity;
        return result;
    }

    template<typename T>
    void my_vector<T>::swap(my_vector <T> &other) noexcept {
        std::swap(array_, other.array_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }

    template<typename T>
    void my_vector<T>::destruct_array() noexcept {
        for (std::size_t i = size_; i > 0; --i) {
            array_[i - 1].~T();
        }
    }

    size_t ceil_power_of_two(size_t n) noexcept {
        std::size_t result = 1;
        while (result < n)
            result *= 2;
        return result;
    }

}// my_vector
#endif

