/// @file
/// @brief string utility and generators

#pragma once

#include <algorithm>
#include <string>

#include <piped/generator.hpp>

namespace piped {

namespace detail {

struct generator_string_split : public generator<generator_string_split> {
public:
    using value_type  = std::string_view;
    using option_type = std::optional<std::string_view>;

private:
    std::string_view _splitstr;
    std::string_view _input;

    size_t _cur{0};
    size_t _end{0};

public:
    generator_string_split(std::string_view splitstr, std::string_view input) //
        : _splitstr(splitstr), _input(input), _end{input.size()}
    {}

    option_type next()
    {
        if(empty()) return empty_v<option_type>;

        auto pos = _input.find(&_splitstr[0], _cur, _splitstr.size());

        if(pos != std::string::npos) {
            auto sv = std::string_view(&_input[_cur], pos - _cur);
            _cur    = pos + _splitstr.size();
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

struct string_split_ {
    std::string_view splitstr;

    template<typename String>
    auto process(const String& s) const
    {
        return generator_string_split(std::move(splitstr), s);
    }
};

} // namespace detail

/**
   @brief Split input based on a `split_string`, generating a `std::string_view`
   for each substring.  Note a std::regex variant is available.

   @details Example:
@code{.cpp}
auto v = "a,b,c" | split(",") | collect<std::vector>;
// Produces ["a","b","c"]
// v is a std::vector<std::string_view>
@endcode

   @ingroup string
 */
inline auto split(std::string_view split_string)
{
    return detail::string_split_{split_string};
}

namespace detail {

struct join_ {
    std::string_view joiner{""};

    template<typename G>
    std::string process(G& g) const
    {
        // Fixme:
        std::string value;

        if(g.empty()) return value;

        {
            auto s = g.next();
            value.append(std::begin(*s), std::end(*s));
        }
        while(!g.empty()) {
            auto s = g.next();
            value.append(joiner);
            value.append(std::begin(*s), std::end(*s));
        }
        return value;
    }

    join_ operator()(std::string_view joiner_) const
    {
        return {joiner_};
    }
};

} // namespace detail

/**
   @brief Join generated string-like objects into a string, with each element
   separated by `joiner`.  The `joiner` defaults to the empty string.

   @details Optionally: `join(std::string_view joiner)`

   Example:
@code{.cpp}
auto s = "a,b,c" | split(",") | join(":");
s == "a:b:c"; // => true
@endcode

   @ingroup string
*/
constexpr detail::join_ join;

} // namespace piped
