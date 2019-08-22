#pragma once

/**
   @dir piped
   @brief PipeDream.
 */
/**
   @file
   @brief Core features.
 */

/**
   @namespace piped
   @brief PipeDream.
 */

/**
   @defgroup comparison Comparison operations
   @brief
*/

/**
   @defgroup generator Generator-related operations
   @brief Lazy and compositional value processing.
 */

/**
  @defgroup mapping Mapping-related operations
  @brief Mapping values to other values.
 */

/**
   @defgroup regex Regular expression operations
   @brief Regular expression utilities.
 */

/**
   @defgroup string String manipulations
   @brief Operations for strings.
 */

/**
  @defgroup match Matching types
  @brief Easily match values by type.
  */

/**
  @defgroup container Container-modifying operations
  @brief Modify containers and their values directly
  */

/**
   @defgroup dev Developer Utility
   @brief Writing your own operations.
 */

/**
   @defgroup type_util Type Utility
   @brief Type utilities of possible use when writing operations
 */

#include <optional>

#include <piped/config.hpp>
#include <piped/ptr.hpp>

namespace piped {

/// Internal classes
namespace detail {

template<typename T>
struct exists : std::true_type {};

template<typename T>
typename std::add_lvalue_reference<T>::type l_declval();

struct has_process {
    template<typename I, typename O>
    static auto sfinae(char) -> exists<decltype(std::declval<O>().process(l_declval<I>()))>;

    template<typename, typename>
    static auto sfinae(int) -> std::false_type;
};

} // namespace detail

/// User-defined literals
namespace literals {}

/**
  @brief The O-behavior of `I | O`. By default, `o.process(i)`, or `o(i)`.
  @ingroup dev
  */
template<typename O>
struct adl_piped_out {
    template<typename I>
    static constexpr bool is_piped = decltype(detail::has_process::sfinae<I, O>('\0'))::value;

    template<typename I, typename Oo = O>
    constexpr static inline auto process(I&& i, Oo&& o) -> decltype(auto)
    {
        return o.process(std::forward<I>(i));
    }
};

/**
   @brief The I-behavior of `I | O`. By default, `adl_piped_out::process()`.
   @ingroup dev
 */
template<typename I>
struct adl_piped {
    template<typename O, typename Ii = I>
    static constexpr bool is_piped =
        adl_piped_out<std::decay_t<O>>::template is_piped<std::decay_t<I>&&>;

    template<typename O, typename Ii = I, typename Oo = std::decay_t<O>>
    constexpr static inline auto process(Ii&& i, O&& o) -> decltype(auto)
    {
        return adl_piped_out<Oo>::process(i, std::forward<O>(o));
    }
};

/**
   @brief The behavior of `A |= C`. By default, `a = a.process(c)`.
   @ingroup dev
 */
template<typename A>
struct adl_piped_assign {
    template<typename C>
    static constexpr bool is_piped = decltype(detail::has_process::sfinae<A, C>('\0'))::value;

    template<typename C>
    static inline auto& process(A& assigned, C&& chain)
    {
        return assigned = chain.process(assigned);
    }
};

/**
   @brief A simple way to implement an operation by specifying a function for `process()`
   @ingroup dev
 */
template<typename F>
struct simple_operation {
    F f;

    simple_operation(const F&) : f(f) {}
    simple_operation(F&& f) : f(f) {}

    template<typename T>
    inline auto process(const T& i) const -> decltype(auto) {
        return f(i);
    }

    template<typename T>
    inline auto process(T& i) const -> decltype(auto) {
        return f(i);
    }
};

/// Type utility for the "empty" value of an option type
/// @ingroup type_util
template<typename T>
struct empty {};

/// Emtpy value for `ptr<T>`
/// @ingroup type_util
template<typename T>
struct empty<extra::ptr<T>> {
    static constexpr extra::ptr<T> value{};
};

/// Empty value for `std::optional<T>`
/// @ingroup type_util
template<typename T>
struct empty<std::optional<T>> {
    static constexpr std::nullopt_t value{std::nullopt};
};

/// Template variable value accessor for `empty<T>`
/// @ingroup type_util
template<typename T>
constexpr auto empty_v = empty<T>::value;

/// Type utility to get iterator begin/end and value types for `T`
/// @ingroup type_util
template<typename T>
struct iterator_for {
    using type       = decltype(std::begin(std::declval<T>()));
    using end_type   = decltype(std::end(std::declval<T>()));
    using value_type = std::remove_reference_t<decltype(*std::declval<type>())>;
};

namespace operators {

template<
    typename I,
    typename O,
    typename F = piped::adl_piped<std::decay_t<I>>,
    typename B = std::enable_if_t<piped::adl_piped<std::decay_t<I>>::template is_piped<std::decay_t<O>>>>
constexpr inline auto operator|(I&& input, O&& output) -> decltype(auto)
{
    return F::process(std::forward<I>(input), std::forward<O>(output));
}

template<
    typename A,
    typename C,
    typename F = piped::adl_piped_assign<std::decay_t<A>>,
    typename   = std::enable_if_t<piped::adl_piped_assign<A>::template is_piped<C>>>
constexpr inline auto operator|=(A&& assigned, C&& chain) -> decltype(auto)
{
    return F::process(std::forward<A>(assigned), std::forward<C>(chain));
}

} // namespace operators

using namespace operators;

} // namespace piped
