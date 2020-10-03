#include "linq.hpp"
#include <cassert>
#include <sstream>
#include <vector>
#include <cmath>
#include <iterator>

using linq::from;

void from_to_vector() {
    std::vector<int> xs = {1, 2, 3};
    std::vector<int> xs_begin = {1, 2, 3};
    std::vector<int> res = from(xs.begin(), xs.end()).to_vector();
    assert(res == xs);
    assert(xs == xs_begin);
}

void from_select() {
    const int xs[] = {1, 2, 3};
    const int xs_begin[] = {1, 2, 3};
    std::vector<int> res = from(xs, xs + 3).select([](int x) { return x + 5; }).to_vector();
    std::vector<int> expected = {6, 7, 8};
    assert(res == expected);
    assert(xs[0] == xs_begin[0]);
    assert(xs[1] == xs_begin[1]);
    assert(xs[2] == xs_begin[2]);
}

void from_where() {
    std::vector<int> xs = {1, 2, 3, 2, 2};
    std::vector<int> res = from(xs.begin(), xs.end()).where([](int x) { return x > 3; }).to_vector();
    std::vector<int> expected = {};
    assert(res == expected);
}

void from_drop() {
    std::vector<int> xs = {1, 2, 3, 2, 2};
    std::vector<int> res = from(xs.begin(), xs.end()).drop(4).to_vector();
    std::vector<int> expected = {2};
    assert(res == expected);
}

void from_take() {
    std::vector<int> xs = {1, 2, 3, 2, 2};
    std::vector<int> res = from(xs.begin(), xs.end()).take(1).to_vector();
    std::vector<int> expected = {1};
    assert(res == expected);
}

void from_where_neq() {
    std::vector<int> xs = {1, 2, 3, 2, 2};
    std::vector<int> res = from(xs.begin(), xs.end()).where_neq(2).to_vector();
    std::vector<int> expected = {1, 3};
    assert(res == expected);
}

void from_drop_select() {
    const int xs[] = {1, 2, 3};
    const int xs_begin[] = {1, 2, 3};
    std::vector<int> res = from(xs, xs + 3).drop(1).select([](int x) { return x + 5; }).to_vector();
    std::vector<int> expected = {7, 8};
    assert(res == expected);
    assert(xs[0] == xs_begin[0]);
    assert(xs[1] == xs_begin[1]);
    assert(xs[2] == xs_begin[2]);
}

void from_until() {
    std::vector<int> xs = {1, 2, 3, 2, 2};
    std::vector<int> res = from(xs.begin(), xs.end()).until([](int x) { return x == 3; }).to_vector();
    std::vector<int> expected = {1, 2};
    assert(res == expected);
}

void from_until_eq() {
    std::vector<int> xs = {1, 2, 3, 2, 2};
    std::vector<int> res = from(xs.begin(), xs.end()).until_eq(3).to_vector();
    std::vector<int> expected = {1, 2};
    assert(res == expected);
}


void example1() {
    int xs[] = {1, 2, 3, 4, 5};

    std::vector<int> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .select([](int x) { return x * x; })  // Возвести в квадрат
                    .where_neq(25)    // Оставить только значения != 25
                    .where([](int x) { return x > 3; })   // Оставить только значения > 3
                    .drop(2)          // Убрать два элемента из начала
                    .to_vector();     // Преобразовать результат в вектор

    std::vector<int> expected = {16};
    assert(res == expected);
}

void example2() {
    std::stringstream ss("1 2 3 -1 4");
    std::istream_iterator<int> in(ss), eof;

    std::vector<int> res =
            from(in, eof)  // Взять числа из входного потока
                    .take(4)       // Не более четырёх чисел
                    .until_eq(-1)  // Перестать читать после прочтения -1
                    .to_vector();  // Получить список считанных чисел

    std::vector<int> expected = {1, 2, 3};
    assert(expected == res);

    int remaining;
    assert(ss >> remaining);
    assert(remaining == 4);
}

void example3() {
    int xs[] = {1, 2, 3, 4, 5};

    std::vector<double> res =
            from(xs, xs + 5)  // Взять элементы xs
                    .select<double>([](int x) { return sqrt(x); })  // Извлечь корень
                    .to_vector();     // Преобразовать результат в вектор

    assert(res.size() == 5);
    for (std::size_t i = 0; i < res.size(); i++) {
        assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
    }
}

void example4() {
    std::stringstream iss("4 16");
    std::stringstream oss;
    std::istream_iterator<int> in(iss), eof;
    std::ostream_iterator<double> out(oss, "\n");

    from(in, eof)    // Взять числа из входного потока
            .select([](int x) { return static_cast<int>(sqrt(x) + 1e-6); })  // Извлечь из каждого корень
            .copy_to(out);  // Вывести на экран

    assert(oss.str() == "2\n4\n");
}

void from_copy_to() {
    std::vector<int> v = {1, 2, 5, 1245};
    std::vector<int> res;
    from(v.begin(), v.end())
            .copy_to(back_inserter(res));
    assert(v == res);
}

void combined1() {
    std::vector<int> v = {1, 3, 5, 7};
    std::vector<int> u = v;
    std::vector<int> res = from(v.begin(), v.end())
            .take(3)
            .select([](int x) { return 2 * x; })
            .drop(1)
            .where([](int x) { return x >= 10; })
            .to_vector();
    std::vector<int> expected = {10};
    assert(res == expected);
    assert(v == u);
}

void combined2() {
    std::vector<int> v = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    std::vector<int> u = v;
    std::vector<int> res = from(v.begin(), v.end())
            .take(9)
            .select([](int x) { return x - 3; })
            .where_neq(0)
            .drop(1)
            .until_eq(2)
            .to_vector();
    std::vector<int> expected = {-1, 1};
    assert(res == expected);
    assert(v == u);
}

void small_buffer_take() {
    std::vector<int> v = {1, 2};
    std::vector<int> u = v;
    std::vector<int> res = from(v.begin(), v.end())
            .take(3)
            .to_vector();
    std::vector<int> expected = {1, 2};
    assert(res == expected);
    assert(v == u);
}

void small_buffer_drop() {
    std::vector<int> v = {1, 2};
    std::vector<int> u = v;
    std::vector<int> res = from(v.begin(), v.end())
            .drop(3)
            .to_vector();
    std::vector<int> expected = {};
    assert(res == expected);
    assert(v == u);
}

int main() {
    from_to_vector();
    from_select();
    from_drop();
    from_take();
    from_drop_select();
    from_where();
    from_until();
    from_until_eq();
    from_where_neq();
    from_copy_to();
    example1();
    example2();
    example3();
    example4();
    combined1();
    combined2();
    small_buffer_take();
    small_buffer_drop();
    return 0;
}
