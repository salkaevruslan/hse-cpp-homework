#include <cstddef>
#include <string>
#include <string_view>
#include <vector>
#include <type_traits>
#include <charconv>
#include <cassert>
#include <cmath>

#if __cplusplus < 201703L
#error At least C++17 is required
#endif

namespace format {

constexpr std::size_t MAX_FORMAT_FUNCTION_OUTPUT_SIZE = 20;

template<typename T>
struct HasFormatImpl {
    typedef std::true_type yes;
    typedef std::false_type no;

    template<typename U>
    static yes test(std::string (U::*format)() const) {
        return yes{};
    }

    template<typename U>
    static auto test(decltype(&U::format), void *) -> decltype(test(&U::format)) {
        return test(&U::format);
    }

    template<typename U>
    static no test(...) {
        return no{};
    }

    static constexpr bool value = std::is_same_v<decltype(test<T>(nullptr, nullptr)), yes>;
};

template<typename T>
constexpr bool has_format_function = HasFormatImpl<T>::value;

template<typename T>
struct isFormattableVector {
    static const bool value = false;
};

template<typename T>
struct isFormattableVector<std::vector<T>> {
    static const bool value = std::is_same_v<T, bool> || std::is_integral_v<T> ||
                              has_format_function<T> || isFormattableVector<T>::value;
};

template<typename T>
constexpr bool is_formattable_vector_v = isFormattableVector<T>::value;

template<typename T>
struct isFormattable {
    static const bool value = std::is_same_v<T, bool> || std::is_integral_v<T> ||
                              has_format_function<T> || is_formattable_vector_v<T>;
};

template<typename T>
constexpr bool is_formattable_v = isFormattable<T>::value;

template<typename T, typename = void>
struct FormatHelper {
};

template<typename T>
struct FormatHelper<T, std::enable_if_t<std::is_same_v<T, bool>>> {
    explicit FormatHelper(const T &value) : value_{value} {
    }

    std::size_t estimate_size() const {
        if (value_)
            return 4;
        else
            return 5;
    }

    void append_to(std::string &s) const {
        if (value_)
            s += "true";
        else
            s += "false";
    }

    const T value_;
};

template<typename T>
struct FormatHelper<T, std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>>> {
    explicit FormatHelper(const T &value) : value_{value} {
    }

    std::size_t estimate_size() const {
        return static_cast<std::size_t>(std::log10((value_ > 0 ? value_ : -value_) + 1) + 3);
    }

    void append_to(std::string &s) const {
        std::string buff(estimate_size(), ' ');
        auto result = std::to_chars(buff.data(), buff.data() + estimate_size(), value_);
        assert(result.ec == std::errc());
        s += std::string_view(buff.data(), result.ptr - buff.data());
    }

    const T value_;
};

template<typename T>
struct FormatHelper<T, std::enable_if_t<is_formattable_vector_v<T>>> {
    explicit FormatHelper(const T &value) : value_{value} {
    }

    std::size_t estimate_size() const {
        std::size_t size = 2 * std::max(static_cast<size_t>(1), value_.size());
        for (std::size_t i = 1; i < value_.size(); ++i) {
            FormatHelper<typename T::value_type> helper(value_[i]);
            size += helper.estimate_size();
        }
        return size;
    }

    void append_to(std::string &s) const {
        s += '{';
        for (std::size_t i = 0; i + 1 < value_.size(); ++i) {
            FormatHelper<typename T::value_type> helper(value_[i]);
            helper.append_to(s);
            s += ", ";
        }
        if (value_.size() > 0) {
            FormatHelper<typename T::value_type> helper(value_.back());
            helper.append_to(s);
        }
        s += '}';
    }

    const T value_;
};

template<typename T>
struct FormatHelper<T, std::enable_if_t<has_format_function<T>>> {
    explicit FormatHelper(const T &value) : value_{value} {
    }

    std::size_t estimate_size() const {
        return MAX_FORMAT_FUNCTION_OUTPUT_SIZE;
    }

    void append_to(std::string &s) const {
        s += value_.format();
    }

    const T value_;
};

template<typename T>
auto make_string(const T &value) -> std::enable_if_t<is_formattable_v<T>, std::string> {
    FormatHelper<T> helper(value);
    std::string formatted;
    formatted.reserve(helper.estimate_size());
    helper.append_to(formatted);
    formatted.shrink_to_fit();
    return formatted;
}
}  // namespace format