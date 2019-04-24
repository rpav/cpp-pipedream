# Building Your Own

Using existing pipedream operations is easy.  Adding your own custom operations is easy as well.  In this chapter, we will take a closer look at how things work, and how you can build your own immediate operations.  This will be the basis for building your own generators.

## What "`|`" Does

The pipe operator does (by [default](/api/group__dev)) a simple thing:

```cpp
auto x = i | o;

// This does:

auto x = o.process(i);
```


## Operation syntax

We have an example like the following:

```cpp
auto v0 = from_to(0,10) | collect<std::vector>;
auto v1 = v
  | each
  | map([](auto i) { return i * i; })
  | collect<std::vector>;
```

Something like `from_to(0,10)` might seem obvious; it's a function.  Or something function-like.  But how do we get `each` and `collect<T>` to work?  They're just values!

```cpp
constexpr each_ each;

template<typename T>
constexpr collect_<T> collect{};
```

Given we know that `|` simply calls `process()`, it's easy to make our own:

@[code](@/../../examples/build_operation1.cpp)

::: warning Note
It is possible to use a `const static inline` variable rather than `constexpr`.  This is not recommended unless you have no choice, as some compilers may require special flags for `static inline` to work correctly, and (hypothetically) this may produce less-optimal code.
:::

## Parameters

What if we want to extend our prior example to add *any* number, not just 1?  This too is quite simple:

@[code](@/../../examples/build_operation2.cpp)

(If you have been wondering why `process()` is used instead of `operator()`, this is why.)

For *required* parameters, simply use a separate function instead of `operator()`:

```cpp
struct add_ { ... /* no operator() */ ... };

inline add_ add(int n) { return {n}; }

auto a = 1 | add; // Now this is an error:
```

## Chaining

We don't have to do anything special here to get chaining:

```cpp
auto a = 1 | add(1) | add(2);
```

Because `process()` returns an `int`, it just gets passed as the input to the *next* operation.

In other words, `process()` should return the value you wish to chain.

## Templates

Of course, we can extend this to types other than `int` by using templates:

@[code](@/../../examples/build_operation3.cpp)


## Summary

This is how pipedream works in a nutshell.  Simply writing structs with `process()` functions should cover most cases.  A `constexpr` value is used to provide the syntax, and `operator()` or a separate function can add parameters.  Templates apply as normal.

Knowing these things, you are now set to understand [generators](/doc/generators).
