/// @file
/// @brief Comparison utility

#pragma once

#include <tuple>

#include <piped/core.hpp>

namespace piped {

namespace detail {

template<bool NOT, typename... Ts>
struct in_ {
    std::tuple<Ts...> vs;

    in_(Ts&&... vs) : vs{vs...} {}

    template<typename T>
    inline bool process(const T& v)
    {
        return std::apply([&](auto&&... vs) -> bool { return (... || (v == vs)) != NOT; }, vs);
    }
};

} // namespace detail

/**
   @brief Test whether the input is in the specified list of values.
   @param vs A list of values which can compare by == to the input.
   @ingroup comparison

   @details This will statically expand to a comparison of `... || v == vs`.

   Example:
@code{.cpp}
if(x | in(1, 2, 3)) {
  // ...
}
@endcode
 */
template<typename... Ts>
auto in(Ts&&... vs)
{
    return detail::in_<false, Ts...>{std::forward<Ts>(vs)...};
}

/**
   @brief Test whether the input is in *not* in the specified list of values.
   @param vs A list of values which can compare by == to the input.
   @ingroup comparison

   @details This will statically expand to a comparison of `... || v == vs`,
   and negate the result.  This is for convenience and deemed less ugly than `if(!(x | in(...)))`.

   Example:
@code{.cpp}
if(x | not_in(1, 2, 3)) {
  // ...
}
@endcode
 */
template<typename... Ts>
auto not_in(Ts&&... vs)
{
    return detail::in_<true, Ts...>{std::forward<Ts>(vs)...};
}

namespace detail {
template<typename K, typename V>
auto map_value_test(const K& test, const std::pair<K, V>& p, const V& def)
{
    if(test == p.first) return p.second;

    return def;
}

template<typename K, typename V, typename... Ts>
auto map_value_test(const K& test, const std::pair<K, V>& p, const Ts&... vs)
{
    static_assert(sizeof...(Ts) != 0 && "Default value required for map_value!");
    if(test == p.first) return p.second;
    return map_value_test(test, vs...);
}
} // namespace detail

/**
   @brief Map the input value to another value, options specified as pairs, with a default at the end
   @param vs A list of one or more `pair<K,V>` ending with a `V default_value`.
   @ingroup comparison

   @details Example:
@code{.cpp}
int foo(int x) {
   using p = std::pair<int,int>;

   return x | map_value<int,int>(
                p(0,1),
                p(1,2),
                p(2,3),
                4);              // Default value if `x` does not match
}
@endcode
   */
template<typename K, typename V, typename... Ts>
auto map_value(const Ts&... vs)
{
    return simple_operation([=](const K& test) { return detail::map_value_test<K, V>(test, vs...); });
}
} // namespace piped
