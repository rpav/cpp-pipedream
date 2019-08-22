/// @file
/// @brief Comparison utility

#pragma once

#include <tuple>

#include <piped/core.hpp>

namespace piped {

namespace detail {

template<typename...Ts>
struct in_ {
    std::tuple<Ts...> vs;

    in_(Ts&&...vs) : vs{vs...} {}

    template<typename T>
    inline bool process(const T& v) {
        return std::apply([&](auto&&... vs) -> bool {
            return (... || (v == vs));
        }, vs);
    }
};
}

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
template<typename...Ts>
detail::in_<Ts...> in(Ts&&...vs) {
    return {std::forward<Ts>(vs)...};
}

}
