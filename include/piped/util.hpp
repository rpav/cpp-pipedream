/// @file
/// @brief otherwise-unclassified utility and generators

#pragma once

#include <algorithm>
#include <limits>
#include <map>
#include <optional>

#include <piped/core.hpp>
#include <piped/generator.hpp>

namespace piped {
namespace detail {
struct each_ {
    template<typename T>
    auto process(T&& v) const
    {
        return generator_from_iterator{std::begin(v), std::end(v)};
    }
};

template<typename T>
struct generator_seq : public generator<generator_seq<T>> {
public:
    using value_type       = T;
    using option_type      = std::optional<value_type>;
    static constexpr T max = std::numeric_limits<T>::max();

public:
    T       cur{0};
    const T last{max};
    const T incr{1};

    generator_seq() = default;
    generator_seq(T first, T last = max, T incr = 1) : cur(first), last(last), incr(incr) {}

    inline option_type next()
    {
        if(!empty()) {
            auto v = cur;
            cur += incr;
            return v;
        }
        return empty_v<option_type>;
    }

    bool empty() const
    {
        return !((incr > 0 && cur < last) || (incr < 0 && cur > last));
    }
};

template<typename G>
struct generator_take : public generator<generator_take<G>> {
public:
    using type        = generator_take;
    using input_type  = std::decay_t<G>;
    using value_type  = typename input_type::value_type;
    using option_type = typename input_type::option_type;

public:
    input_type input;
    size_t     count{0};

    generator_take(input_type g, size_t c) : input{std::move(g)}, count{c} {}

    inline option_type next()
    {
        if(!empty()) {
            --count;
            return input.next();
        }
        return empty_v<option_type>;
    }

    inline bool empty() const
    {
        return (count == 0 || input.empty());
    }
};

struct take_ {
    size_t count{0};

    template<typename G>
    generator_take<G> process(G&& input) const
    {
        return {input, count};
    }
};

template<typename G>
struct generator_skip : public generator<generator_skip<G>> {
public:
    using type        = generator_skip;
    using input_type  = std::decay_t<G>;
    using value_type  = typename input_type::value_type;
    using option_type = typename input_type::option_type;

public:
    input_type input;

    generator_skip(input_type g, size_t c) : input{std::move(g)}
    {
        while(c > 0 && !input.empty()) {
            --c;
            input.next();
        }
    }

    inline option_type next()
    {
        return input.next();
    }

    inline bool empty() const
    {
        return input.empty();
    }
};

struct skip_ {
    size_t count{0};

    template<typename G>
    generator_skip<G> process(G&& input) const
    {
        return {input, count};
    }
};

template<template<typename...> typename T, typename... Ts>
struct collect_ {
    template<typename G, typename Gd = std::decay_t<G>>
    inline T<typename Gd::value_type, Ts...> process(G&& g) const
    {
        T<typename Gd::value_type> r;
        decltype(g.next())         v;

        while(v = g.next(), v) {
            r.emplace_back(*v);
        }

        return r;
    }
};

template<typename... Ts>
struct collect_<std::map, Ts...> {
    template<
        typename G,
        typename Gd       = std::decay_t<G>,
        typename map_type = std::map<
            std::tuple_element_t<0, typename Gd::value_type>,
            std::tuple_element_t<1, typename Gd::value_type>,
            Ts...>>
    inline map_type process(G&& g) const
    {
        map_type           m;
        decltype(g.next()) v;

        while((v = g.next())) {
            m.try_emplace(std::get<0>(*v), std::get<1>(*v));
        }

        return m;
    }
};

template<typename G, typename F>
struct generator_filter : public generator<generator_filter<G, F>> {
public:
    using type          = generator_filter;
    using input_type    = std::decay_t<G>;
    using function_type = F;
    using value_type    = typename input_type::value_type;
    using option_type   = typename input_type::option_type;

public:
    input_type    input;
    function_type function;

    inline option_type next()
    {
        while(auto v = input.next()) {
            if(!v) break;
            if(function(*v)) return v;
        }

        return empty_v<option_type>;
    }

    inline bool empty() const
    {
        return input.empty();
    }
};

template<typename F>
struct filter_ {
    using function_type = F;
    function_type function;

    template<typename G>
    inline generator_filter<G, F> process(G&& input) const
    {
        return {{}, input, function};
    }
};

} // namespace detail

/** @addtogroup generator
 * @{
 */
/**
   @brief `each` generates values from an input container

   @details Example:

@code{.cpp}
   std::vector<int> v{1,2,3};
   auto g = v | each
     | map([](auto i){ return i+1; })
     | collect<std::vector>;
@endcode
 */
constexpr each_ each;

/**
   @brief Generate a numeric sequence starting at `n`
   @param n Starting value
   @param by Increment, defaults to `T{1}`

   @details Behavior is undefined if the next value exceeds what `T` can
   represent.
 */
template<typename T>
inline generator_seq<T> from(T n, T by = T{1})
{
    T last = by > 0 ? std::numeric_limits<T>::max() : std::numeric_limits<T>::lowest();
    return {n, last, by};
}

/**
  @brief Generate a half-open numeric sequence from `first` to before `limit`.

  @details Values proceed from `first` to `limit`, incremented by `by`.
  `limit` does not have to be a value in the sequence. `incr` may be negative.

  @param first Starting value
  @param limit Output will stop before this
  @param by Increment, defaults to `T{1}`
 */
template<typename T>
inline generator_seq<T> from_to(T first, T limit, T by = T{1})
{
    return {first, limit, by};
}

/**
   @brief Generate the first `n` values input.

   @details Example:
@code{.cpp}
auto v = from(5) | take(3) | collect<std::vector>;
// => [5,6,7]
//
// Normally just use from_to() here, though.
@endcode
 */
inline take_ take(size_t count)
{
    return {count};
}

/**
   @brief Immediately skip the first `n` values from input.  May empty input.
   @details Example:
@code{.cpp}
auto v = from_to(5,10) | skip(1) | collect<std::vector>;
// => [6,7,8,9]
@endcode

   Note, values are skipped immediately because it would otherwise be impossible to
   tell the correct value of `empty()`.  It is required that if `empty()` returns
   false, `next()` return a non-empty value.
 */
inline skip_ skip(size_t n)
{
    return {n};
}

/**
   @brief Collect input values into the container `T`, e.g., `collect<std::vector>`.

   @details Element type is determined by input. Use `map_to` to convert things
   along the way.  Elements are inserted by `emplace_back()` by default.

@code{.cpp}
auto v  = from_to(0,5)            | collect<std::vector>;   // std::vector<int>
auto v1 = from_to<size_t>(10,100) | collect<std::vector>;   // std::vector<size_t>
auto v2 = from_to(0.0f,-10.0f)    | collect<std::vector>;   // std::vector<float>
@endcode

   There is explicit support for building `std::map` if the input is a `std::tuple`
   of at least 2 values; the first will be the key, the second the value.  Elements are
   inserted by `try_emplace()`.  See `zip` for an example.
 */
template<template<typename...> typename T, typename... Ts>
constexpr collect_<T, Ts...> collect{};

/**
   @brief Generate values from input when `f(v)` returns true.

   @details If `f(v)` returns false, values will be generated repeatedly until input is exhausted or true
   is returned.

@code{.cpp}
auto v = from_to(0,10)
  | filter([](auto v) { return (v % 2) != 0; })
  | collect<std::vector>;

// => [1,3,5,7,9]
@endcode
 */
template<typename F>
filter_<F> filter(const F& f)
{
    return {f};
}

namespace detail {

template<typename F, typename T>
struct reduce_init_ {
    T initial;
    F function;

    template<typename G>
    inline auto process(G& g) const
    {
        auto r    = initial;
        auto next = g.next();

        while(next) {
            r    = function(r, *next);
            next = g.next();
        }

        return r;
    }
};

template<typename F>
struct reduce_ {
    F function;

    template<typename G>
    inline auto process(G& g) const
    {
        using val_t = typename G::value_type;

        if(g.empty()) return val_t{};

        auto r    = *g.next();
        auto next = g.next();

        while(next) {
            r    = function(r, *next);
            next = g.next();
        }

        return r;
    }
};

} // namespace detail

/**
  @brief Reduce/fold input given an initial value

  @details Example:
@code{.cpp}
auto v = from_to(1,10) | collect<std::vector>;
auto i = v | each | reduce(std::plus<>(), 1);
// -> 46
@endcode

  @returns The result of repeatedly calling `r = f(r,v)`, or `r`,
  where `r` is the initial value.

 */
template<typename F, typename T>
inline reduce_init_<F, T> reduce(F f, T initial)
{
    return {initial, f};
}

/**
  @brief Reduce/fold input.  Input is a generator.

  @details Example:
@code{.cpp}
auto v = from_to(1,10) | collect<std::vector>;
auto i = v | each | reduce(std::plus<>());
// -> 45
@endcode

  @returns The result of repeatedly calling `r = f(r,v)`, or `r`,
  where `r` is a default-initialized value.
 */
template<typename F>
inline reduce_<F> reduce(F f)
{
    return {f};
}

/** @} */

namespace detail {
template<typename F>
struct call_ {
    F f;

    template<typename T>
    auto process(T&& v) const
    {
        return f(v);
    }
};

} // namespace detail

/**
  @brief Call `f` with input

  @details Example:
@code{.cpp}
// Obtuse addition
auto v = 1 | call([](auto x) { return x + 1; });
@endcode

  @param f *Callable*
  @ingroup misc
 */
template<typename F>
call_<F> call(F&& f)
{
    return {f};
}

} // namespace piped
