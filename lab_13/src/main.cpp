#include "my_array.h"

#include <cstddef>
#include <iostream>

using lab_13::my_array;

namespace test {
    template<typename T, std::size_t N>
    void test_core() {
        my_array<T, N> a;
        const my_array<T, N> &ca = a;
        a.empty();
        ca.empty();
        a.size();
        ca.size();

        a.at(0);
        ca.at(0);
        a[0];
        ca[0];
        (void) static_cast<const T &>(a[0]);
        (void) static_cast<const T &>(ca[0]);
    }

    template<typename T>
    void test_assign() {
        my_array<T, 10> a;
        const my_array<T, 10> &ca = a;
        a.fill(T());

        a[0] = T();
        a[0] = a[0];
        a[0] = ca[0];
    }

    template<>
    void test_assign<int>() {
        my_array<int, 10> a;
        a.fill(123);
        a[0] = 5;
        a[1] = a[0];
        a[0] = 0;
        assert(a[1] == 5);
        assert(a[0] == 0);
    }

    template<>
    void test_assign<bool>() {
        my_array<bool, 10> a;
        a[0] = true;
        a[1] = a[0];
        a[0] = false;
        assert(a[1] == true);
        assert(a[0] == false);
    }

    template<typename T>
    void test_size() {
        assert(sizeof(my_array<T, 10>) == 10 * sizeof(T));
    }

    template<>
    void test_size<bool>() {
        assert(sizeof(my_array<bool, 1>) == 1);
        assert(sizeof(my_array<bool, 8>) == 1);
        assert(sizeof(my_array<bool, 10>) == 2);
    }

    template<typename T>
    void test_fill() {
        my_array<T, 10> a;
        a.fill(T());
        for (std::size_t i = 0; i < 10; ++i)
            assert(a[i] == T());
    }

    template<>
    void test_fill<int>() {
        my_array<int, 10> a;
        a.fill(321);
        for (std::size_t i = 0; i < 10; ++i)
            assert(a[i] == 321);
    }

    template<>
    void test_fill<bool>() {
        my_array<bool, 10> a;
        a.fill(true);
        for (std::size_t i = 0; i < 10; ++i)
            assert(a[i]);
    }

    template<typename T>
    void test_at() {
        my_array<T, 10> a;
        a.at(0) = T();
        assert(a.at(0) == T());
        try {
            a.at(12);
            std::abort();
        } catch (const std::out_of_range &er) {
        }
    }

    template<>
    void test_at<int>() {
        my_array<int, 10> a;
        a.fill(15);
        my_array<int, 10> b;
        b = a;
        b.at(0) = 5;
        assert(b.at(1) == 15);
        assert(b.at(0) == 5);
    }

    template<>
    void test_at<bool>() {
        my_array<bool, 10> a;
        a.fill(true);
        my_array<bool, 10> b;
        b = a;
        b.at(0) = false;
        for (std::size_t i = 1; i < 10; ++i)
            assert(b.at(i) == true);
        assert(b.at(0) == false);
    }

    template<typename T>
    void test_operator_at() {
        my_array<T, 10> a;
        a[0] = T();
        assert(a[0] == T());
    }

    template<>
    void test_operator_at<int>() {
        my_array<int, 10> a;
        a.fill(15);
        my_array<int, 10> b;
        b = a;
        b[0] = 5;
        assert(b[1] == 15);
        assert(b[0] == 5);
    }

    template<>
    void test_operator_at<bool>() {
        my_array<bool, 10> a;
        a.fill(true);
        my_array<bool, 10> b;
        b = a;
        b.at(0) = false;
        for (std::size_t i = 1; i < 10; ++i)
            assert(b[i] == true);
        assert(b[0] == false);
    }
}

class NonCopyable {
public:
    NonCopyable() {}

private:
    NonCopyable(const NonCopyable &);

    NonCopyable &operator=(const NonCopyable);
};

int main() {
    test::test_core<int, 10>();
    test::test_core<bool, 10>();
    test::test_core<NonCopyable, 10>();

    test::test_fill<char>();
    test::test_fill<int>();
    test::test_fill<bool>();

    test::test_assign<char>();
    test::test_assign<int>();
    test::test_assign<bool>();

    test::test_at<char>();
    test::test_at<int>();
    test::test_at<bool>();

    test::test_operator_at<char>();
    test::test_operator_at<int>();
    test::test_operator_at<bool>();

    test::test_size<int>();
    test::test_size<bool>();
}

