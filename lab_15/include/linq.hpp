#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

namespace linq {
namespace impl {

template<typename T, typename Iter>
class range_enumerator;

template<typename T>
class drop_enumerator;

template<typename T>
class take_enumerator;

template<typename T, typename U, typename F>
class select_enumerator;

template<typename T, typename F>
class until_enumerator;

template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:
    virtual const T &operator*() const = 0; // Получает текущий элемент.
    virtual enumerator<T> &operator++() = 0;  // Переход к следующему элементу
    virtual explicit operator bool() const = 0;  // Возвращает true, если есть текущий элемент

    auto drop(size_t count) {
        return drop_enumerator<T>(*this, count);
    }

    auto take(size_t count) {
        return take_enumerator<T>(*this, count);
    }

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, std::move(func));
    }

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, std::move(func));
    }

    auto until_eq(const T &val) {
        return this->until([val](const T &elem) { return elem == val; });
    }

    template<typename F>
    auto where(F func) {
        return where_enumerator<T, F>(*this, std::move(func));
    }

    auto where_neq(const T &val) {
        return this->where([val](const T &elem) { return elem != val; });
    }

    std::vector<T> to_vector() {
        std::vector<T> res;
        this->copy_to(std::back_inserter(res));
        return res;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (*this) {
            *(it++) = *(*this);
            ++(*this);
        }
    }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
    }

    const T &operator*() const override {
        return *begin_;
    }

    enumerator<T> &operator++() override {
        if (*this)
            ++begin_;
        return *this;
    }

    explicit operator bool() const override {
        return begin_ != end_;
    }

private:
    Iter begin_, end_;
};

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    drop_enumerator(enumerator<T> &parent, size_t count) : parent_(parent), count_(count) {
        for (size_t i = 0; i < count; ++i)
            ++parent_;
    }

    const T &operator*() const override {
        return *parent_;
    }

    enumerator<T> &operator++() override {
        ++parent_;
        return *this;
    }

    explicit operator bool() const override {
        return static_cast<bool>(parent_);
    }

private:
    enumerator<T> &parent_;
    size_t count_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T> &parent, size_t count) : parent_(parent), count_(count) {
    }

    const T &operator*() const override {
        return *parent_;
    }

    enumerator<T> &operator++() override {
        if (count_ > 0)
            --count_;
        if (count_ > 0)
            ++parent_;
        return *this;
    }

    explicit operator bool() const override {
        return (count_ > 0) && static_cast<bool>(parent_);
    }

private:
    enumerator<T> &parent_;
    size_t count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
    select_enumerator(enumerator<U> &parent, F func) : parent_(parent), func_(std::move(func)) {
    }

    const T &operator*() const override {
        if (!applied_)
            apply();
        applied_ = true;
        return curr_;
    }

    enumerator<T> &operator++() override {
        ++parent_;
        applied_ = false;
        return *this;
    }

    explicit operator bool() const override {
        return static_cast<bool>(parent_);
    }

private:
    void apply() const {
        curr_ = func_(*parent_);
    }

    mutable bool applied_{false};
    mutable T curr_;
    enumerator<U> &parent_;
    F func_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), func_(std::move(predicate)) {
        check();
    }

    const T &operator*() const override {
        return *parent_;
    }

    enumerator<T> &operator++() override {
        if (!*this)
            return *this;
        ++parent_;
        check();
        return *this;
    }

    explicit operator bool() const override {
        return static_cast<bool>(parent_) && !is_end_;
    }

private:
    void check() {
        is_end_ = func_(*parent_);
    }

    bool is_end_{false};
    enumerator<T> &parent_;
    F func_;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
    where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), func_(std::move(predicate)) {
        get_next();
    }

    const T &operator*() const override {
        return *parent_;
    }

    enumerator<T> &operator++() override {
        ++parent_;
        get_next();
        return *this;
    }

    explicit operator bool() const override {
        return static_cast<bool>(parent_);
    }

private:
    void get_next() {
        while (parent_ && !func_(*parent_))
            ++parent_;
    }

    enumerator<T> &parent_;
    F func_;
};

} // namespace impl

template<typename T>
auto from(T begin, T end) {
    return impl::range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

} // namespace linq

#endif

