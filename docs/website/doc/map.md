# Generators

Generators are a form of "iterator" that you may have encountered.  Rather than the `std` concept of a container with `begin()`/`end()` returning "index values" which may be incremented, compared, etc, a generator is a much simpler concept:

* `next()` returns an optional next value
* `empty()` returns whether the generators will produce further values

Unlike `begin()`/`end()`, range tracking is not left to the user, nor must it be *fit* into the model of a `begin()`/`end()` container returning comparable values.  This makes things simpler to implement, simpler to use, less error-prone, and far more flexible.

## A Simple Generator

The front page example is a good place to start:

@[code](@/../../examples/gen_simple1.cpp)

There are a few things of note here we will explore in the following sections.

### CRTP and Iterators

```cpp
public generator<generator_from<T>>
```

Generators should inherit from `generator<CRTP>` using CRTP (i.e., pass itself).  The `generator` class provides "iterator transparency," i.e. it implements `begin()`/`end()` so you can just use your iterator for range-based for:

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

* `option_type`, which is a type optionally representing a value, whose *bool-convertible* value indicates whether a value is, in fact, present
* `value_type` is the type that `option_type` holds

Note that `T*` (or [`ptr<T>`](/api/classpiped_1_1ptr)) is a valid `option_type`, as well as `std::optional<T>`.  These should cover most circumstances.

### Methods

```cpp
option_type next()        { ... }
bool        empty() const { ... }
```

All `next()` must do is provide a valid next value.  All empty must do is indicate whether or not `next()` *will* provide a valid next value.

::: danger Required
If `empty()` returns true, `next()` must provide a valid value.
:::

This will have implications for *chaining* generators, notably, a generator can't say it's not empty, and the following call to `next()` notices its source container is empty and provide nothing.  This generally only a consideration when an operation preemptively consumes values, e.g., [skip](/api/group__generator#skip-size-t-n).


## Chaining

If generators stood alone, they would not be very interesting.  With chaining, we get lazy, composable operations:

```cpp
auto g = from_to(0,5) | map([](auto x) { return x + 1 });
```

Note that nothing happens here except the construction of the generator `g`.  We could `collect<>` these into a container, or iterate them with `for`, stopping at any time.

### Implementing "my_map"

So, how is `map()` implemented?  Simply, both `next()` and `empty()` first get values from an *input* generator, then perform their action.  Note that `map` is the complicated case: it's a generator with an input generator!  If we wanted something like `collect<>`, that's not a generator, and can simply be implemented with `process()`.

At first glance, perhaps this may seem complicated (or not).  Fear not!  We will break it down piece by piece:

@[code](@/../../examples/gen_chain1.cpp)

### Types

First, we have a similar CRTP-inherited `generator<T>`.  This should not require further explanation, but it pays to do this first when implementing your own generator.

```cpp
public generator<my_generator_map<G, F>>
```

Next, if you're not used to type traits, we have what are perhaps the scariest lines in the code:

```cpp
    using input_type       = std::decay_t<G>;
    using input_value_type = typename input_type::value_type;

    using value_type  = decltype(std::declval<F>()(std::declval<input_value_type>()));
```

Horror!  Well, not quite:

* `decay_t<T>` means we want `T` if we get `T&`
* `input_type` is therefore our input generator type
* `input_type::value_type` gets the .. input value type
* `using value_type = ...` is a bit hairy, but it says, "what is returned by `F(input_value_type)`", where `F` is the user-provided function

These are the most difficult lines.  And not the most interesting!  That's what follows.

### Delegating

```cpp
    input_type input;
    F          function;
```

Here is where the input generator lives.  In fact, for a long chain of generators, each stores the prior in relatively close proximity.  The compiler should have a fairly easy time with optimization.  Also, we store the function, of course.

Our `next()` and `empty()` do very little:

```cpp
    option_type next()
    {
        if(auto v = input.next(); v) return function(*v);

        return std::nullopt;
    }

    bool empty() const { return input.empty(); }
```

For the most part, this delegates to the input.  If `next()` finds a value, it calls `function` and returns, or nothing.  `empty()` asks if the input is empty.

This is the actual majority of the code.  The rest is more or less boilerplate, which we will cover next.


### Boilerplate

```cpp{6}
template<typename F>
struct my_map_ {
    F function;

    template<typename G>
    inline my_generator_map<G, F> process(G&& input) const
    {
        return {{}, input, function};
    }
};
```

Hiding in the middle of the highlighted line is our `process()` method.  Remember, this is what `operator|` calls to make things happen, so we will have:

```cpp
(a my_map_).process(input generator);
```

This process function returns the `my_generator_map` we created, populating it with `input` and `function`.  Note the first `{}` in `{{}, input, function}` is a blank initialization for the inherited `generator` class.

The final piece of the puzzle is the function:

```cpp
template<typename F>
my_map_<F> my_map(const F& f) { return {f}; }
```

We use a function, because we want to require the user specify `function`, and not have a default.

### All together now

```cpp
auto g = from_to(0,5) | my_map([](auto v) { return v + 1 });
```

What this does, loosely speaking:

* `operator|(from_to(...), my_map(...))` which calls...
* `my_map_.process(from_to)` which returns...
* `my_generator_map(from_to(...), function...)`

Phew!  But, all of that is automatic.  What we had to implement seems like quite a bit, but was only around 30 lines of the actual, well-spaced code, which:

* Figures out our types... this was a fairly complex case
* Stores our input generator and function
* Calls through to the input, and conditionally processes the output
* Some boilerplate

Now we have an independent, composable, lazy-processing map operation, that can be chained with other operations or iterated directly!
