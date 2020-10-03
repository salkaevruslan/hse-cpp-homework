#ifndef MY_VECTOR_TEST_H
#define MY_VECTOR_TEST_H

#include "Test.h"
#include "my_vector.h"
#include <sstream>

namespace test {

    template<typename T>
    class my_vector_test final : public Test {
    public:
        my_vector_test(T t1, T t2) : sample1(t1), sample2(t2) {
        }

        void run_tests() override {
            test_default_constructor();
            test_copy_constructor();
            test_move_constructor();
            test_assignment_operator_lvalue();
            test_assignment_operator_rvalue();
            test_size();
            test_capacity();
            test_empty();
            test_reserve();
            test_operator_at();
            test_push_back_lvalue();
            test_push_back_rvalue();
            test_pop_back();
            test_clear();
            test_write();
        }

        void run_default_constructible_tests() {
            test_size_constructor();
            test_resize();
            test_operator_at_assign();
        }

        void test_default_constructor() {
            my_vector::my_vector<T> v;
            DO_CHECK(v.empty());
        }

        void test_size_constructor() {
            my_vector::my_vector<T> v(5);
            DO_CHECK(v.size() == 5);
            DO_CHECK(v.capacity() == 8);
            DO_CHECK(test_equals(v[1], T()));
        }

        void test_copy_constructor() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            my_vector::my_vector<T> v2(v);
            DO_CHECK(v2.size() == 2);
            DO_CHECK(test_equals(v2[0], sample1));
            DO_CHECK(test_equals(v2[1], sample2));
        }


        void test_move_constructor() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            my_vector::my_vector<T> v2(std::move(v));
            DO_CHECK(v2.size() == 2);
            DO_CHECK(test_equals(v2[0], sample1));
            DO_CHECK(test_equals(v2[1], sample2));
        }

        void test_assignment_operator_lvalue() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            my_vector::my_vector<T> v2;
            v2.push_back(sample2);
            v = v2;
            DO_CHECK(v.size() == 1);
            DO_CHECK(test_equals(v[0], sample2));
        }

        void test_assignment_operator_rvalue() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            my_vector::my_vector<T> v2;
            v2.push_back(sample2);
            v = std::move(v2);
            DO_CHECK(v.size() == 1);
            DO_CHECK(test_equals(v[0], sample2));
        }

        void test_resize() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            v.resize(1);
            DO_CHECK(v.size() == 1);
            v.resize(5);
            DO_CHECK(test_equals(v[1], T()));
        }

        void test_size() {
            my_vector::my_vector<T> v;
            DO_CHECK(v.size() == 0);
            v.push_back(sample2);
            DO_CHECK(v.size() == 1);
        }

        void test_capacity() {
            my_vector::my_vector<T> v;
            DO_CHECK(v.capacity() == 0);
            v.push_back(sample2);
            DO_CHECK(v.capacity() == 1);
            v.push_back(sample1);
            DO_CHECK(v.capacity() == 2);
            v.push_back(sample2);
            DO_CHECK(v.capacity() == 4);
        }

        void test_empty() {
            my_vector::my_vector<T> v;
            DO_CHECK(v.empty());
            v.push_back(sample1);
            DO_CHECK(!v.empty());
        }

        void test_reserve() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.reserve(10);
            DO_CHECK(v.size() == 1);
            DO_CHECK(v.capacity() == 16);
        }

        void test_operator_at() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            DO_CHECK(test_equals(v[0], sample1));
            DO_CHECK(test_equals(v[1], sample2));
            try {
                v.push_back(v[100]);
                DO_CHECK(false);
            } catch (const std::range_error&) {
                DO_CHECK(true);
            }
        }

        void test_operator_at_assign() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            DO_CHECK(test_equals(v[0], sample1));
            DO_CHECK(test_equals(v[1], sample2));
            v[1] = v[0];
            v[0] = sample2;
            DO_CHECK(test_equals(v[0], sample2));
            DO_CHECK(test_equals(v[1], sample1));
            try {
                v[2] = sample1;
                DO_CHECK(false);
            } catch (const std::range_error&) {
                DO_CHECK(true);
            }
        }

        void test_push_back_lvalue() {
            my_vector::my_vector<T> v;
            v.push_back(sample2);
            DO_CHECK(v.size() == 1);
            DO_CHECK(test_equals(v[0], sample2));
        }

        void test_push_back_rvalue() {
            my_vector::my_vector<T> v;
            v.push_back(T(sample2));
            DO_CHECK(v.size() == 1);
            DO_CHECK(test_equals(v[0], sample2));
        }

        void test_pop_back() {
            my_vector::my_vector<T> v;
            v.push_back(sample2);
            v.pop_back();
            DO_CHECK(v.size() == 0);
            try {
                v.pop_back();
                DO_CHECK(false);
            } catch (const std::logic_error&) {
                DO_CHECK(true);
            }
        }

        void test_clear() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            v.clear();
            DO_CHECK(v.size() == 0);
        }

        void test_write() {
            my_vector::my_vector<T> v;
            v.push_back(sample1);
            v.push_back(sample2);
            std::stringstream ss;
            std::stringstream ss1;
            std::stringstream ss2;
            ss << v;
            ss1 << sample1, ss2 << sample2;
            std::string s1, s2;
            while (ss1 >> s1) {
                ss >> s2;
                DO_CHECK(s1 == s2);
            }
            while (ss2 >> s1) {
                ss >> s2;
                DO_CHECK(s1 == s2);
            }
        }

    private:
        T sample1;
        T sample2;

        bool test_equals(T t1, T t2) {
            std::stringstream ss1;
            std::stringstream ss2;
            ss1 << t1, ss2 << t2;
            std::string s1, s2;
            try {
                while (ss1 >> s1) {
                    ss2 >> s2;
                    if (s1 != s2)
                        return false;
                }
                while (ss2 >> s2) {
                    ss1 >> s1;
                    if (s1 != s2)
                        return false;
                }
            } catch (...) {
                return false;
            }
            return true;
        }
    };
}// test

#endif

