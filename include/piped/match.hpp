#pragma once

#include <functional>
#include <variant>

#include <piped/core.hpp>

namespace piped {

namespace detail {

template<typename M, typename T, typename... Ts>
struct find_helper {
    static constexpr bool value = std::is_same_v<M, T> || find_helper<M, Ts...>::value;
};

template<typename M, typename T>
struct find_helper<M, T> {
    static constexpr bool value = std::is_same_v<M, T>;
};

template<typename M, typename... Ts>
struct find {
    static constexpr bool value = find_helper<M, Ts...>::value;
};

} // namespace detail

/**
  @brief Behavior for matching `M` on a type `T` for `match<M>`

  @details For instance, a `variant<Ts...>` is customized so `match<M>`
  will match the variant if it currently holds the specified type.

  @ingroup match type_util
 */
template<typename M, typename T>
struct adl_match {
    static constexpr bool can_match = std::is_same_v<std::decay_t<T>, M>;

    template<typename S>
    static M* does_match(S* v)
    {
        return can_match ? v : nullptr;
    }
};

template<typename M, typename... Ts>
struct adl_match<M, std::variant<Ts...>> {
    static constexpr bool can_match = find<M, Ts...>::value;

    template<typename S>
    inline static auto* does_match(S* v)
    {
        return can_match ? std::get_if<M>(v) : nullptr;
    }
};

namespace detail {

template<typename T, typename F>
struct match_helper {
    F f;

    template<typename S>
    inline std::decay_t<S>* process(S&& v) const
    {
        return process(&v);
    }

    template<typename S>
    inline S* process(S* v) const
    {
        if constexpr(adl_match<T, S>::can_match) {
            ptr<T> actual;

            if(v && (actual = adl_match<T, S>::does_match(v))) {
                f(*actual);
                return nullptr;
            }
        }
        return v;
    }
};

template<typename F>
struct match_else_helper {
    F f;

    template<typename T>
    inline void process(T&& v) const
    {
        return process(&v);
    }

    template<typename T>
    inline void process(T* v) const
    {
        if(v) f();
    }
};

template<typename T>
struct match_ {
    template<typename F>
    match_helper<T, F> operator()(F f) const
    {
        return {f};
    }

    template<typename F>
    match_helper<T, F> operator<=(F f) const
    {
        return {f};
    }
};

struct match_else_ {
    template<typename F>
    match_else_helper<F> operator()(F f) const
    {
        return {f};
    }

    template<typename F>
    match_else_helper<F> operator<=(F f) const
    {
        return {f};
    }
};

} // namespace detail

/**
  @brief Match by type.

  @details Example:
@code{.cpp}
template<typename T>
void F(T v) {
    v
    | match<int>   <= [](auto i) { say("F int"); }
    | match<float> <= [](auto f) { say("F float"); }
    | match_else   <= [](auto v) { say("None of the above!"); }
    ;
}
@endcode

  This provides a pipe-based visitor syntax for matching values on type. The
  function provided to the first encountered match will be called; further
  matches will be skipped.  `match_else` can be used to match any other case.

  One can customize how type matching is done by specializing `adl_match`.

  `operator<=` is ~~abused~~ overloaded to provide slightly nicer syntax.  One
  can also call using `match<T>([](...){ })`.

  @see `match_else`

  @ingroup match
 */

template<typename T>
constexpr match_<T> match{};

/**
  @brief Match anything.
  @see `match`

  @ingroup match
  */
constexpr match_else_ match_else{};
} // namespace piped
