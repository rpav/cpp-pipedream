# cpp-pipedream

## C++ quiz

```cpp
// How do you make a vector of sequential numbers?

auto v0 = from_to(0,10) | collect<std::vector>;


// How do you make one of floats from 0.0..0.9 by 0.1?

auto v1 = from_to(0.0f, 1.0f, 0.1f) | collect <std::vector>;


// Take a string "a,b,c" and make a map like {{"a": 1}, {"b": 2}, ...}.
// Use one line of code.

auto m0 = zip("a,b,c" | split(","), from(1)) | collect<std::map>;


// How do you split a string by *regex*, and join it with ","?

auto s0 = "a,b:c,d#e" | split("[,:#]"_re) | join(",");


// Split the same string but iterate until you find "c", without doing extra
// work (e.g. splitting/matching more of the string than necessary)

auto g = "a,b:c,d#e" | split("[,:#]"_re);

for(auto s : g)
   if(s == "c") break;


// Write a visitor for a std::variant<int,float,std::string> that
// adds or appends 1.

std::variant<int,float,std::string> va0 = 42.0f;

va0
| match<int>         <= [](auto& i) { i += 1; }
| match<float>       <= [](auto& f) { f += 1.0f; }
| match<std::string> <= [](auto& s) { s += "1"; }
;

// ^- for a template: same code
```


## What is cpp-pipedream?

There are clearly other libraries that make use of "pipe syntax" to do
similar things:

 * [range-v3](https://github.com/ericniebler/range-v3), the basis of the range TS
 * [pipe](https://github.com/vladris/pipe), for functional-style operations

However, cpp-pipedream is neither of these.  Rather, this is a library
has a simple design goal, stated a few ways:

 1. Make things that should be simple, simple
 2. Make a general, user-extensible mechanism for chain-call APIs

This means that things like "split a string" or "build a vector" or
"erase some values" or even "write an iterator" should be simple,
intuitive, and require minimal code.

<div class="info custom-block">

In essence, read `|` as a generalized `.`, where `foo | bar()` is like `foo.bar()`.

</div>



## More Code, Less Code

Today, to write "an iterator" in C++ requires a considerable amount of
code.  Let's say we want a very simple thing: to iterate from a number,
by an increment, without bound.  E.g.,

```cpp
for(auto i : from(1)) { ... }

// =

for(auto i = 1; ; ++i) { ... }
```

Here is the code based on a simple "from" counter, container-style form:

```cpp
// This is not cpp-pipedream

struct from_end { };

template<typename T>
struct from_iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T*;
    using reference = T&;

    from_iterator(T v, T i) : _v(v), _i(i) { }

    T& operator*() { return _v; }
    T* operator->() { return &_v; }

    from_iterator& operator++() { _v += _i; return *this; }

    bool operator==(const from_iterator &i) const { return _v == i._v; }
    bool operator!=(const from_iterator &i) const { return _v != i._v; }
    bool operator==(const from_end &) const { return false; }
    bool operator!=(const from_end &) const { return true; }

private:
    T _v;
    T _i;
};

template<typename T>
struct from {
    using iterator = from_iterator<T>;

    from(T v, T i = T(1)) : _v(v), _i(i) { }

    iterator begin() const { return iterator(_v, _i); }
    from_end end() const { return {}; }

private:
    T _v;
    T _i;
};
```

Instead:

```cpp
// Pipe dream

template<typename T>
struct generator_from : public generator<generator_from<T>> {
    using value_type = T;
    using option_type = std::optional<T>;

    T cur{};
    const T incr{1};

    option_type next() { auto v = cur; cur += incr; return v; }
    bool empty() const { return false; }
};

template<typename T>
inline generator_from<T> from(T n, T by = T{1}) {
    return {{}, n, by};
}
```

And this works.  This is composable, and iterable:

```cpp
auto v = from(1) | take(3) | collect<std::vector>;

for(auto i : from(1))
    if(i > 5) break;
```

This is `cpp-pipedream`.


## What this is not

This library is not:

 * About ranges
 * About functional-style operations
 * About generators and iterators
 * About rewriting every piece of code to include `|`

Some of these things are covered, mainly because they're useful and
low-hanging fruit, and test the design.  But usefulness, pragmatism,
and simplicity *are* the goal.


## Support

This requires c++17.  It seems possible to backport: some `zip` usage of
`if constexpr` would need backported, and iterator handling would need
adjusted, as well as pulling in backports of things like `optional` and
`string_view`.  This is not a current goal.

Tests pass on the following:

* clang-7.0.1 (libc++ or libstdc++)
* gcc-8.2.1 (libstdc++)
* MSVC 19.15.26730.0

It likely works on slightly older versions as well.

## More Documentation

There is [more documentation](https://rpav.github.io/cpp-pipedream/)
on usage and extension.

## License

Copyright 2019 Ryan Pavlik

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
