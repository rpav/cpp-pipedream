# Generators

This chapter discusses how to write your own custom [generator operations](/doc/basics#Operations).  If you have not read how to [build operations](/doc/building), you should start there.

Generators are a form of "iterator" that you may have encountered.  Rather than the `std` concept of a container with `begin()`/`end()` returning "index values" which may be incremented, compared, etc, a generator is a much simpler concept:

* `next()` returns an optional next value
* `empty()` returns whether the generators will produce further values

Unlike `begin()`/`end()`, range tracking is not left to the user, nor must it be *fit* into the model of ranges or a `begin()`/`end()` container returning comparable values.  This makes things simpler to implement, simpler to use, less error-prone, and far more flexible.

## A Simple Generator

The front page example is a good place to start:

@[code](@/../../examples/gen_simple1.cpp)

There are a few things of note here we will explore in the following sections.

### CRTP and Iterators

```cpp
public generator<generator_from<T>>
```

Generators should inherit from `generator<CRTP>`, with itself as the type.  The `generator` class provides "iterator transparency:" it implements `begin()`/`end()` so you can just use your generator for range-based for:

```cpp
    for(auto i : my_from(1)) {
        std::cout << i << std::endl;
        if(i > 5) break;
    }
```

No additional code is necessary!

::: warning Note
Using these for purposes other than range-based for *may* be possible, but caution is recommended.  Few restrictions are places on generators, but these iterators have *more* restrictions:

* Copies of iterators are not independent, but `++it` may invalidate others
* The lifetime of values returned by `*it` *might* not exceed the next call to `++it`
* These are not indexes and storing them is not useful
:::

### Types

```cpp
    using value_type  = T;
    using option_type = std::optional<T>;
```

Generators should always define two types:

* `option_type`, which is a type optionally representing a value, whose *bool-conversion* indicates whether a value is present
* `value_type` is the type that `option_type` holds

Note that `T*` (or [`ptr<T>`](/api/classpiped_1_1ptr)) is a valid `option_type`, as well as `std::optional<T>`.  These should cover most circumstances.

### Methods

```cpp
option_type next()        { ... }
bool        empty() const { ... }
```

All `next()` must do is provide a valid next value.  All empty must do is indicate whether or not `next()` *will* provide a valid next value.

::: danger Required
If `empty()` returns false, `next()` must provide a valid value.
:::

This will have implications for *chaining* generators, notably, a generator can't say it's not empty, and the following call to `next()` notices its source is empty and provide nothing.  This is rarely an issue, with only one example, [skip](/api/group__generator#skip-size-t-n).


## Chaining

If generators stood alone, they would not be very interesting.  With chaining, we get lazy, composable operations:

```cpp
auto g = from_to(0,5) | map([](auto x) { return x + 1 });
```

Note that nothing happens here except the construction of the generator `g`.  We could `collect<>` these into a container, or iterate them with `for`, stopping at any time.

### An "add" generator

So, what if instead of `x | add(1)` from the [prior example](/doc/building), we wanted to make a *generator*, so we could do something like this:

```cpp{2}
auto v = from_to(0,10) | collect<std::vector>;
auto g = v | each | add(5);

for(auto i : g)
    std::cout << i << std::endl;
```

There will be two main differences:

1. We will need a `generator_add`
1. `process` will need to return this instead of immediately processing input

We will also introduce one new thing that was not discussed [above](#A-Simple-Generator): an input generator!  First, let's look at the code, and go through piece by piece:

@[code transclude={7-26}](@/../../examples/gen_chain1.cpp)

### Input Generators

The first thing of note is that we have a new template parameter, `G`.  This will be our *input generator*, i.e., the thing we're taking values from.  Initialization is as one should expect:

@[code transclude={7-8}](@/../../examples/gen_chain1.cpp)

We crtp-inherit from `generator` to automatically get iterators.  The next bit is new:

@[code transclude={9-9}](@/../../examples/gen_chain1.cpp)

If you are not familiar with C++ type traits, `std::decay_t<G>` basically says, if we get some `Type&`, we're interested in `Type`.  Below, you can see where this is actually used:

@[code transclude={14-14}](@/../../examples/gen_chain1.cpp)

Note:

::: tip
Input generators are *stored locally* in the generator.  This is nice and can let the compiler optimize.  But...
:::

::: danger
You must use `std::decay_t<G>`, or it will store a *reference to a temporary*, which will make your code crash, or worse.
:::

The heart of generator chains is that they can mostly delegate, and simply perform their task.  We can see this is the case here:

@[code highlight={3,9} transclude={17-25}](@/../../examples/gen_chain1.cpp)

We take from `input`, and if `input` returns a value, perform our operation.  Likewise, this generator is simply transforming, has no inherent end, and is finished when input is finished.  Pretty simple!

### Pipe Operation

Putting this together, we need the standard things.  Similar to [the original](/doc/building#Templates), we have a struct with `process` and a function for compulsory argument.  This time, we return the generator, instead of immediately processing:

@[code transclude={28-40}](@/../../examples/gen_chain1.cpp)

Note this time, for `process`, we have a `template<typename G>`, which template based on the *input generator*, and we pass this right along to `generator_add`, along with our increment type and value.

### All Together

This is what the code looks like:

@[code](@/../../examples/gen_chain1.cpp)

All in all, while we have 30-some odd (well-spaced) lines to implement
this, there was nothing particularly superfluous or redundant.  Ideally, it would be nice to reduce a few more lines of type declaration and similar, but alas! We will need to wait for metaclasses.
