/// @file
/// @brief `std::regex` utility and generators

#pragma once

#include <optional>
#include <regex>

#include <piped/core.hpp>
#include <piped/generator.hpp>
#include <piped/map.hpp>
#include <piped/ptr.hpp>

namespace piped {

namespace literals {

/// Regular expression literals
namespace regex {

/**
  @brief `"foo"_re -> std::regex{"foo"}`
  @ingroup regex

  @details Example:
@code{.cpp}
using namespace piped::literals;

auto s = "ab" | replace(".b"_re, "x"); // => "xb"
@endcode
  */
inline std::regex operator""_re(const char* s, size_t sz) // "
{
    return {s, sz};
}

} // namespace regex
} // namespace literals

namespace detail {

struct replace_ {
    std::regex      re;
    extra::ptr<const char> fmt;

    std::string process(const std::string& s) const
    {
        return std::regex_replace(s, re, fmt.get());
    }
};

} // namespace detail

/**
  @brief `std::string` replace by regex
  @details Example:

@code{.cpp}
std::string s = "abc";
s |= replace(".b", "xb");
s == "xbc"; // => true
@endcode

  (Note that `std::regex_replace` expects a null-terminated string, and thus
  `std::string_view` can't be used for `fmt` input here.)

  @ingroup regex
  @param re A `std::regex`.
  @param fmt `const char*` convertible replacement format, as per `std::regex_replace`
  @return A new string with replacement done.
 */
inline detail::replace_ replace(std::regex re, extra::ptr<const char> fmt)
{
    return {std::move(re), fmt};
}

namespace detail {

template<typename String>
struct generator_regex_matches : public generator<generator_regex_matches<String>> {
public:
    using input_type  = String;
    using value_type  = std::match_results<const char*>; // fixme: non-char-based strings
    using option_type = extra::ptr<value_type>;

private:
    std::regex _re;
    value_type _m;

    const input_type& _input;
    size_t            _cur{0};
    size_t            _end{0};

public:
    generator_regex_matches(std::regex re, const String& s)
        : _re(std::move(re))
        , _input{s}
        , _end{static_cast<size_t>(std::distance(std::begin(s), std::end(s)))}
    {}

    option_type next()
    {
        if(_cur >= _end) return nullptr;

        if(std::regex_search(&_input[_cur], &_input[_end], _m, _re)) {
            _cur += _m.length();
            return &_m;
        }

        return empty_v<option_type>;
    }

    bool empty() const
    {
        return _cur >= _end;
    }
};

template<typename S>
generator_regex_matches(std::regex re, const S&)->generator_regex_matches<S>;

struct each_match_ {
    std::regex re;

    template<typename String>
    auto process(const String& s) const
    {
        return generator_regex_matches(re, s);
    }

    // fixme: ref_or_value
    template<typename String>
    auto process(const String&&) const = delete;
};

} // namespace detail

/**
  @param re A `std::regex`.
  @returns Match generator

  @ingroup generator regex

  @brief Match input with `re`, and generate each match as output.

  @details Example:
@code{.cpp}
auto v = "X:Y:Z:"
  | each_match(".:"_re)
  | map_nth(0)
  | map_to<std::string_view>
  | collect<std::vector>;

// Produces ["X:", "Y:", "Z:"] as a vector of string_view of
// the original string.
@endcode
 */
inline detail::each_match_ each_match(std::regex re)
{
    return {std::move(re)};
}

/**
  @brief Implicitly convert regex sub-matches to `std::string_view`.
 */
template<>
struct adl_map_to<std::sub_match<const char*>, std::string_view> {
    static auto convert(const std::sub_match<const char*>& v)
    {
        return std::string_view{v.first, (size_t)std::distance(v.first, v.second)};
    }
};

namespace detail {

struct generator_regex_split : public generator<generator_regex_split> {
public:
    using value_type  = std::string_view;
    using option_type = std::optional<std::string_view>;

private:
    std::regex       _re;
    std::string_view _input;

    size_t _cur{0};
    size_t _end{0};

public:
    generator_regex_split(std::regex re, std::string_view input) //
        : _re(std::move(re)), _input(input), _end{input.size()}
    {}

    option_type next()
    {
        if(empty()) return empty_v<option_type>;

        std::match_results<const char*> m;

        if(std::regex_search(&_input[_cur], &_input[_end], m, _re)) {
            auto sv = std::string_view(&_input[_cur], m.position());
            _cur += m.position() + m.length();
            return sv;
        }

        auto sv = std::string_view(&_input[_cur], _end - _cur);
        _cur    = _end;
        return sv;
    }

    bool empty() const
    {
        return _cur >= _end;
    }
};

struct regex_split_ {
    std::regex re;

    template<typename String>
    auto process(const String& s) const
    {
        return generator_regex_split(re, s);
    }
};

} // namespace detail

/**
  @brief Split input based on a `std::regex`, generating each substring.
  Note a `std::string` variant is available.

  @ingroup generator regex

  @param re Regular expression to match split delimiter
  */
inline auto split(std::regex re)
{
    return detail::regex_split_{std::move(re)};
}

} // namespace piped
