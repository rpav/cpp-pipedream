/// @file piped/ptr.hpp
/// @brief A better `T*`

#pragma once

#include <cstdlib>
#include <type_traits>

#include <piped/config.hpp>

namespace piped {

/**
 @brief A transparent pointer wrapper. This functions as an `option_type`, i.e.
 implements unary `*`, and is bool-convertible.

 @ingroup dev


 This is nice for three primary reasons:

  - Simple, debug-optional, cross-platform `nullptr`-check
  - Default `nullptr` initialization!
  - All of `ptr<T>`, `const ptr<T>`, `ptr<const T>`, and `const ptr<const T>` act exactly
    as you'd expect.

 You may be asking, "why check for nullptr?  Won't it just crash anyway?"  Note the following
 will probably not crash:

@code{.cpp}
class C {
  void foo() {
     // Do things not referencing instance data members
  }

};

C *c = nullptr;
c->foo();
@endcode

 This may lead to unobvious errors elsewhere if you're not checking
 `this` pointers in your debugger.  `ptr<T>`, with debugging enabled,
 will cause an abort at the point you do `c->foo()`.
 */
template<typename T>
class ptr {
    template<typename U>
    friend class ptr;

public:
    using type       = T*;
    using value_type = T;

protected:
    T* _ptr{nullptr};

    static inline T* ensure_ptr(T* p)
    {
        if constexpr(config::ptrCheck) {
            if(!p) std::abort();
        }
        return p;
    }

    inline T* ensure_ptr() const
    {
        return ensure_ptr(_ptr);
    }
    inline T* ensure_ptr()
    {
        return ensure_ptr(_ptr);
    }

public:
    ptr() = default;             ///< Default-initialize to `nullptr`
    ptr(T* p) : _ptr(p) {}       ///< Default convert from `T*`a
    ptr(const ptr& p) = default; ///< Copy.

    /// Handle `ptr<T>` to `ptr<const T>`
    template<typename S, typename = std::enable_if_t<not std::is_same_v<S, T>>>
    ptr(const ptr<S>& p) : _ptr(p._ptr)
    {}

    /// Return a reference.
    T& operator*() const
    {
        return *ensure_ptr();
    }
    /// Non-const.
    T& operator*()
    {
        return *ensure_ptr();
    }

    /// Dereference.
    T* operator->() const
    {
        return ensure_ptr();
    }

    /// Non-const.
    T* operator->()
    {
        return ensure_ptr();
    }

    /// `true` if pointer is not `nullptr`.
    operator bool()
    {
        return _ptr != nullptr;
    }

    /// Non-operator, affirmative check for `nullptr`.
    bool is_null()
    {
        return _ptr == nullptr;
    }

    /// Non-cast-operator conversion to pointer.
    T* get() const
    {
        return _ptr;
    }
    /// Non-const
    T* get()
    {
        return _ptr;
    }

    /// Cast operator to `T*`.
    operator const T*() const
    {
        return _ptr;
    }

    /// Non-const
    operator T*()
    {
        return _ptr;
    }

    /// Assign from `const ptr<T>`.  `T`'s const-ness is orthogonal.
    ptr& operator=(const ptr& p)
    {
        _ptr = p._ptr;
        return *this;
    }
};

} // namespace piped
