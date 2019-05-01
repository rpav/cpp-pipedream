#pragma once

/**
  @file
  @brief Generator-related classes and utility
  */

#include <iterator>
#include <optional>
#include <type_traits>

#include <piped/core.hpp>

namespace piped {

/**
  @addtogroup dev
  @{
  */

namespace detail {

/// `generator<T>` builds a C++-style "container" using this, consisting of the appropriate
/// methods and a hack to test for end.  You should generally not have to use this explicitly.
template<typename T>
class iterator_from_generator {
public:
    using generator   = std::decay_t<T>;
    using value_type  = typename generator::value_type;
    using option_type = typename generator::option_type;

private:
    generator&  _gen;
    option_type _val;

    inline void fill_next()
    {
        _val = _gen.next();
    }

public:
    iterator_from_generator(generator& g) : _gen(g)
    {
        fill_next();
    }
    iterator_from_generator(const iterator_from_generator&)     = default;
    iterator_from_generator(iterator_from_generator&&) noexcept = default;

    inline bool operator==(const iterator_from_generator& b) const
    {
        return _gen == b;
    }

    inline bool operator==(const generator&) const
    {
        return _val == empty_v<option_type>;
    }

    inline bool operator!=(const iterator_from_generator& b) const
    {
        return _gen != b;
    }

    inline bool operator!=(const generator&) const
    {
        return _val != empty_v<option_type>;
    }

    value_type& operator*()
    {
        return *_val;
    }

    inline iterator_from_generator& operator++()
    {
        fill_next();
        return *this;
    }

    inline option_type operator->()
    {
        return _val;
    }
};

template<typename T>
iterator_from_generator(T)->iterator_from_generator<T>;

} // namespace detail

/**
   @brief
   Generator should be a base class for user-built generators.
   It provides methods to implicitly use the generator as a C++-style container
   with `begin()`/`end()`.

   @details
   Generators should publicly inherit this with CRTP, and implement:

        using value_type = ...;
        using option_type = some_option_type<value_type>;

        option_type next();
        bool empty() const;

   `option_type` is any type implementing `operator*()` to dereference a value, and
   should be implicitly bool-convertible to describe whether it contains a value
   or not.  Dereferencing with no value is undefined.  Pointers (prefer `ptr<T>`)
   and `std::optional<T>` are two examples.

   If `empty()` returns true, `next()` is expected to return `empty_v<T>`.

   Likewise, if `empty()` returns false, `next()` is expected to produce a value.

   Note generators do not have to generalize on any `T`: `value_type` may be fixed,
   but it is expected to be defined, along with `option_type`.
 */
template<typename CRTP>
struct generator {
    using actual_generator = CRTP;
    using iterator         = detail::iterator_from_generator<actual_generator>;
    using end_iterator     = actual_generator&;

    /// This returns an iterator suitable for range-based-for-like iteration.
    /// It is not expected that you can use algorithms, or store or reuse copies.
    inline iterator begin()
    {
        return {*static_cast<actual_generator*>(this)};
    }

    /// This returns the generator as an end iterator, which when compared with
    /// the iterator returned by `begin()`, will appropriately check if the generator
    /// is empty.
    inline end_iterator end()
    {
        return *static_cast<actual_generator*>(this);
    }
};

/**
  Produce values given C++-style begin/end iterators.

  Note this should *not* be used for iterators whose value is invalidated after incrementing.
  This generally includes any "stashing" iterator, such as `std::regex_iterator` or, apparently,
  `std::filesystem::path::iterator`.  These iterators are fundamentally broken and you should
  simply write a generator for the underlying type.
*/
template<typename B_Iter, typename E_Iter = B_Iter>
struct generator_from_iterator : public generator<generator_from_iterator<B_Iter, E_Iter>> {

public:
    using child_iterator     = std::decay_t<B_Iter>;
    using child_end_iterator = std::decay_t<E_Iter>;

    using value_type  = std::remove_reference_t<decltype(*std::declval<child_iterator>())>;
    using option_type = extra::ptr<value_type>;

private:
    child_iterator     _cur;
    child_end_iterator _end;

public:
    inline extra::ptr<value_type> next()
    {
        if(empty()) return nullptr;

        auto v = &*_cur;
        ++_cur;
        return v;
    }

    inline bool empty() const
    {
        return _cur == _end;
    }

    generator_from_iterator() = default;
    generator_from_iterator(child_iterator begin, child_end_iterator end)
        : _cur(std::move(begin)), _end(std::move(end))
    {}
    generator_from_iterator(const generator_from_iterator&) = default;
    generator_from_iterator(generator_from_iterator&&) noexcept(
        std::is_nothrow_move_assignable<B_Iter>::value&&
            std::is_nothrow_move_assignable<E_Iter>::value) = default;

    generator_from_iterator& operator=(const generator_from_iterator&) = default;
    generator_from_iterator& operator=(generator_from_iterator&&) = default;
};

template<typename B, typename E>
generator_from_iterator(B, E)->generator_from_iterator<B, E>;

/** @} */

} // namespace piped
