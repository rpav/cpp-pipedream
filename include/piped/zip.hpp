/// @file
/// @brief generating pairs and tuples

#pragma once

#include <tuple>
#include <utility>

#include <piped/core.hpp>
#include <piped/generator.hpp>

namespace piped {

namespace detail {

template<typename... Ts>
struct generator_zip : public generator<generator_zip<Ts...>> {
public:
    using type        = generator_zip;
    using value_type  = std::tuple<typename Ts::value_type...>;
    using option_type = std::optional<value_type>;

private:
    std::tuple<Ts...> _generators;

public:
    generator_zip(Ts&&... vs) : _generators{std::move(vs)...} {}

    option_type next()
    {
        if(empty()) return empty_v<option_type>;

        return std::apply([](auto&... gs) { return std::make_tuple(*gs.next()...); }, _generators);
    }

    bool empty() const
    {
        return any_empty<>();
    }

private:
    template<size_t N = 0>
    inline bool any_empty() const
    {
        if constexpr(N < sizeof...(Ts)) {
            if(std::get<N>(_generators).empty()) {
                return true;
            }

            // MSVC appears to have if-constexpr issue, or `if constexpr`
            // is overly-strict
            if constexpr(N + 1 < sizeof...(Ts))
                return any_empty<N + 1>();
        }

        return false;
    }
};

} // namespace detail

/**
  @brief Combine multiple generators' output into a `std::tuple`.
  @param vs A series of generators.
  @ingroup generator

  @details This will generate a `std::tuple` based on the `value_type` of
  each specified generator.  It will be empty when *any* of the generators
  are empty.

  Example:
@code{.cpp}
auto m = zip("a,b,c" | split(","), from(1)) | collect<std::map>;
// Produces {{"a",1}, {"b",2}, {"c",3}}
//
// Note however this is a map<string_view, int>
@endcode
 */
template<typename... Ts>
auto zip(Ts&&... vs)
{
    return detail::generator_zip<Ts...>(std::forward<Ts>(vs)...);
}

} // namespace piped
