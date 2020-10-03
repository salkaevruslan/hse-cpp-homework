#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <cassert>
#include <cstring>

namespace lab_13 {

    template<typename T, std::size_t N>
    class my_array {
    public:
        const T &at(std::size_t index) const;

        T &at(std::size_t index);

        const T &operator[](std::size_t index) const noexcept;

        T &operator[](std::size_t index) noexcept;

        bool empty() const noexcept;

        std::size_t size() const noexcept;

        void fill(const T &val) noexcept;

    private:
        T data_[N];
    };


    template<std::size_t N>
    class my_array<bool, N> {
    private:
        class proxy {
        public:
            proxy(uint8_t *data, std::size_t bit);

            proxy &operator=(bool val) noexcept;

            proxy &operator=(const proxy &other) noexcept;

            operator bool() const;

        private:
            uint8_t *data_;
            int bit_;
        };

    public:
        bool at(std::size_t index) const;

        bool operator[](std::size_t index) const noexcept;

        proxy at(std::size_t index);

        proxy operator[](std::size_t index) noexcept;

        bool empty() const noexcept;

        std::size_t size() const noexcept;

        void fill(bool val) noexcept;

    private:
        uint8_t data_[static_cast<std::size_t>(N / 8 + static_cast<std::size_t>(N % 8 != 0))];
    };

    template<typename T, std::size_t N>
    const T &my_array<T, N>::at(std::size_t index) const {
        if (index >= N)
            throw std::out_of_range("Out of range, on index:" + std::to_string(index));
        return data_[index];
    }

    template<typename T, std::size_t N>
    T &my_array<T, N>::at(std::size_t index) {
        if (index >= N)
            throw std::out_of_range("Out of range, on index:" + std::to_string(index));
        return data_[index];
    }

    template<typename T, std::size_t N>
    const T &my_array<T, N>::operator[](std::size_t index) const noexcept {
        assert(index < N);
        return data_[index];
    }

    template<typename T, std::size_t N>
    T &my_array<T, N>::operator[](std::size_t index) noexcept {
        assert(index < N);
        return data_[index];
    }

    template<typename T, std::size_t N>
    bool my_array<T, N>::empty() const noexcept {
        return (N == 0);
    }

    template<typename T, std::size_t N>
    std::size_t my_array<T, N>::size() const noexcept {
        return N;
    }

    template<typename T, std::size_t N>
    void my_array<T, N>::fill(const T &val) noexcept {
        for (std::size_t i = 0; i < N; ++i) {
            data_[i] = val;
        }
    }


    template<std::size_t N>
    my_array<bool, N>::proxy::proxy(uint8_t *data, std::size_t bit): data_(data),
                                                                     bit_(bit) {
    }

    template<std::size_t N>
    auto my_array<bool, N>::proxy::operator=(bool val) noexcept -> proxy & {
        *data_ &= ~(1 << bit_);
        *data_ |= (val << bit_);
        return *this;
    }

    template<std::size_t N>
    auto my_array<bool, N>::proxy::operator=(
            const my_array<bool, N>::proxy &other) noexcept -> proxy & {
        if (&other == this)
            return *this;
        else {
            this->operator=(static_cast<bool>(other));
            return *this;
        }
    }

    template<std::size_t N>
    my_array<bool, N>::proxy::operator bool() const {
        return (*data_ & (1 << bit_));
    }


    template<std::size_t N>
    bool my_array<bool, N>::at(std::size_t index) const {
        if (index >= N)
            throw std::out_of_range("Out of range, on index:" + std::to_string(index));
        return (data_[index / 8] & (1 << (index % 8)));
    }

    template<std::size_t N>
    typename my_array<bool, N>::proxy my_array<bool, N>::at(std::size_t index) {
        if (index >= N)
            throw std::out_of_range("Out of range, on index:" + std::to_string(index));
        return proxy(&data_[index / 8], index % 8);
    }

    template<std::size_t N>
    bool my_array<bool, N>::operator[](std::size_t index) const noexcept {
        assert(index < N);
        return (data_[index / 8] & (1 << (index % 8)));
    }

    template<std::size_t N>
    typename my_array<bool, N>::proxy my_array<bool, N>::operator[](std::size_t index) noexcept {
        assert(index < N);
        return proxy(&data_[index / 8], index % 8);
    }

    template<std::size_t N>
    bool my_array<bool, N>::empty() const noexcept {
        return (N == 0);
    }

    template<std::size_t N>
    std::size_t my_array<bool, N>::size() const noexcept {
        return N;
    }

    template<std::size_t N>
    void my_array<bool, N>::fill(bool val) noexcept {
        uint8_t tmp = (val ? (1 << 8) - 1 : 0);
        std::size_t size = static_cast<std::size_t>(N / 8 + static_cast<std::size_t>(N % 8 != 0));
        memset(data_, tmp, size);
    }

}  // namespace lab_13


#endif  // MY_ARRAY_H_
