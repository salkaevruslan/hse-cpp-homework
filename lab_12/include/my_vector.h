#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <iostream>

namespace my_vector {

    template<typename T>
    class my_vector final {
    public:
        my_vector() noexcept;

        explicit my_vector(std::size_t n);

        my_vector(const my_vector<T> &other);

        my_vector(my_vector<T> &&other) noexcept;

        my_vector &operator=(const my_vector<T> &other);

        my_vector &operator=(my_vector<T> &&other) noexcept;

        ~my_vector();

        std::size_t size() const noexcept;

        std::size_t capacity() const noexcept;

        bool empty() const noexcept;

        void resize(std::size_t n);

        void reserve(std::size_t n);

        T &operator[](std::size_t index);

        const T &operator[](std::size_t index) const;

        void push_back(const T &t);

        void push_back(T &&t);

        void pop_back();

        void clear() noexcept;

    private:
        size_t size_;
        size_t capacity_;
        T *array_;

        void swap(my_vector<T> &other) noexcept;

        void destruct_array() noexcept;

        static my_vector allocate_vector(std::size_t capacity);
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const my_vector<T> &v);

    std::size_t ceil_power_of_two(std::size_t n) noexcept;
}

#include "my_vector_impl.h"

#endif

