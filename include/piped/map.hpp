/// @file
/// @brief Generators for mapping values to other values.

#pragma once

#include <optional>

#include <piped/generator.hpp>

namespace piped {

namespace detail {

template<typename G, typename F>
struct generator_map : public generator<generator_map<G, F>> {
public:
    using type             = generator_map;
    using input_type       = std::decay_t<G>;
    using function_type    = F;
    using input_value_type = typename input_type::value_type;
    using value_type       = decltype(std::declval<F>()(std::declval<input_value_type>()));
    using option_type      = std::optional<value_type>;

public:
    input_type    input;
    function_type function;

    inline option_type next()
    {
        auto v = input.next();

        if(v) return function(*v);

        return empty_v<option_type>;
    }

    inline bool empty() const
    {
        return input.empty();
    }
};

template<typename F>
struct map_ {
    using function_type = F;
    function_type function;

    template<typename G>
    inline generator_map<G, F> process(G&& input) const
    {
        return {{}, input, function};
    }
};

} // namespace detail

/**
  @brief Value generated from `f(input)`.
  @ingroup generator mapping

  @details Example:
@code{.cpp}
auto v = from_to(1,4)
  | map([](auto v) { return v + 1; })
  | collect<std::vector>;

/// Produces [2,3,4] as a vector<int>
@endcode
 */
template<typename F>
map_<F> map(const F& f)
{
    return {f};
}

/**
  @brief This is used to customize type conversion.
  @details By default, this is a simple `static_cast<To>(From)`.  Generally you should not
  even have to customize this: simply implement the appropriate operators.

  _Sometimes_ you may want specific behavior to convert between values, perhaps for
  types you do not control in code you don't own or can't modify.  In that case,
  a specific implementation may be useful.

@code{.cpp}
struct myvec2 { float x, y; };

template<>
struct adl_map_to<myvec2, glm::vec2> {
    static inline glm::vec2 convert(const myvec2& v) {
        return {v.x, v.y};
    }
};
@endcode

  @ingroup dev mapping
 */
template<typename From, typename To>
struct adl_map_to {
    static inline To convert(const From& v)
    {
        return static_cast<To>(v);
    }
};

namespace detail {

template<typename G, typename T>
struct generator_map_to : public generator<generator_map_to<G, T>> {
public:
    using type             = generator_map_to;
    using input_type       = std::decay_t<G>;
    using input_value_type = typename input_type::value_type;
    using value_type       = std::decay_t<T>;
    using option_type      = std::optional<T>;

public:
    input_type input;

    inline option_type next()
    {
        auto v = input.next();

        if(v) return adl_map_to<input_value_type, value_type>::convert(*v);

        return empty_v<option_type>;
    }

    inline bool empty() const
    {
        return input.empty();
    }
};

template<typename T>
struct map_to_ {
    template<typename G>
    inline generator_map_to<G, T> process(G&& g) const
    {
        return {{}, g};
    }
};

} // namespace detail

/**
   @brief Map inputs to a new type.
   @ingroup generator mapping
   @details By default, this is a `static_cast<To>`.  See @ref adl_map_to for customizing
   this.

   Example:
@code{.cpp}
auto v = "a,b,c" | split(",") | map_to<std::string> | collect<std::vector>
// Produces a vector<string>, creating new strings,
// rather than a vector<string_view>
@endcode
  */
template<typename T>
constexpr map_to_<T> map_to{};

namespace detail {
template<typename G>
struct generator_map_nth : public generator<generator_map_nth<G>> {
public:
    using type       = generator_map_nth;
    using input_type = std::decay_t<G>;

    // fixme: should handle references
    using value_type =
        std::decay_t<decltype(std::declval<typename input_type::value_type>()[std::declval<size_t>()])>;
    using option_type = std::optional<value_type>;

public:
    input_type input;
    size_t     index{0};

    generator_map_nth(input_type g, size_t index) : input{std::move(g)}, index{index} {}

    inline option_type next()
    {
        auto v = input.next();
        if(v) {
            return (*v)[index];
        }

        return empty_v<option_type>;
    }

    inline bool empty() const
    {
        return input.empty();
    }
};

struct map_nth_ {
    size_t index{0};

    template<typename G>
    inline auto process(const G& g) const
    {
        return generator_map_nth<G>{g, index};
    }
};

} // namespace detail

/**
   @brief Produce the nth value of input using `operator[]`.
   @ingroup generator mapping
   @details Example:

@code{.cpp}
auto s = "X:Y:Z:"s;
auto v = s
  | each_match(".:")             // match_data
  | map_nth(0)                   // nth submatch
  | map_to<std::string_view>
  | collect<std::vector>;

// Produce ["X:", "Y:", "Z:"] as a `vector<string_view>`
@endcode
 */
inline map_nth_ map_nth(size_t nth)
{
    return {nth};
}

} // namespace piped
