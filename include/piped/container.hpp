/**
  @file
  @details Container-modifying commands
 */

#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>

#include <piped/core.hpp>

namespace piped {

namespace detail {

template<typename F>
struct erase_if_ {
    F function;

    template<typename C>
    inline C& process(C& c) const
    {
        c.erase(std::remove_if(c.begin(), c.end(), function), c.end());
        return c;
    }
};

} // namespace detail

/**
  @brief Modifying operation which **immediately** erases all values where `f(v)` returns true.
  @param f A function which takes a value and returns a bool-convertible value
  @returns A reference to the (now-transformed) input
  @ingroup container

  @details Uses `std::erase` and `std::remove_if`.  Input should be a container, not a generator.
  (Use `filter` for filtering generated values.)  Example:

@code{.cpp}
auto v = from_to(1,10) | collect<std::vector>;

v | erase_if([](auto v) { return v > 1 || v < 9; });

// v is now [1,9]
@endcode
 */
template<typename F>
inline detail::erase_if_<F> erase_if(const F f)
{
    return {f};
}

namespace detail {

template<typename F>
struct sort_ {
    F function;

    template<typename C>
    inline C& process(C& c) const
    {
        std::sort(std::begin(c), std::end(c), function);
        return c;
    }

    template<typename Ff>
    constexpr inline sort_<Ff> operator()(const Ff& f) const
    {
        return {f};
    }
};

} // namespace detail

/**
  @brief Modifying operation which **immediately** sorts values on the input container.
  @param function Optional function which is used to sort.  Defaults to `std::less<>()`.
  @returns Input container reference

  @ingroup container

  @details Example:
@code{.cpp}
std::vector<int> v{1,5,3,7,-22,1,10};
v | sort;                      // => [-22, 1, 1, 3, 5, 7, 10]
v | sort(std::greater<>());    // => [10, 7, 5, 3, 1, 1, -22]
@endcode
 */
constexpr detail::sort_<decltype(std::less<>())> sort{std::less<>()};

namespace detail {

template<typename F>
struct unique_ {
    F function;

    template<typename C>
    inline C& process(C& c) const
    {
        c.erase(std::unique(std::begin(c), std::end(c), function), c.end());
        return c;
    }
};

} // namespace detail

/**
  @brief Modifying operation which **immediately** performs a `std::unique` on the input
  @param function Optional function which is used to unique.  Defaults to `std::equal_to<>()`.
  @returns Input container reference

  @ingroup container

  @details Example:
@code{.cpp}
std::vector<int> v{1,5,3,7,-22,1,10};
v | sort | unique;             // => [-22, 1, 3, 5, 7, 10]
@endcode

  This uses `std::erase` and `std::unique`.
 */
constexpr detail::unique_<decltype(std::equal_to<>())> unique{std::equal_to<>()};


/**
   @brief Return the `std::set_difference` between the input and `c`

   @ingroup container
 */
template<typename C>
inline auto difference(const C& c)
{
    return simple_operation([&](const C& d) {
        C rc;
        std::set_difference(d.begin(), d.end(), c.begin(), c.end(), std::inserter(rc, rc.begin()));
        return rc;
    });
};

/**
   @brief Return the `std::set_symmetric_difference` between the input and `c`

   @ingroup container
 */
template<typename C>
inline auto symmetric_difference(const C& c)
{
    return simple_operation([&](const C& d) {
        C rc;
        std::set_symmetric_difference(d.begin(), d.end(), c.begin(), c.end(), std::inserter(rc, rc.begin()));
        return rc;
    });
};

/**
   @brief Modifying operation that appends `v` to input.

   @ingroup container
 */
template<typename C>
inline auto append(const C& other) {
    return simple_operation([&](C& c) -> C& {
        c.insert(c.end(), other.begin(), other.end());
        return c;
    });
}

} // namespace piped
