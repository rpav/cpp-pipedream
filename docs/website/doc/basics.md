# Basics

## Operations

This is a simple overview of how to use pipedream *operations* (the term that will generally be used for something on the right hand side of `|`). These generally consist of:

* A simple immediate value, which can be modifying or not, such as `replace` or `erase_if`
* A *generator* that takes and/or produces values

In general, operations should return either a new value, or a reference to the original value, to readily support chaining.

### Immediate Operations

The simplest operations are *immediate*: that is, they take a value, and return a value.  For instance, `split` is an immediate operation:

```cpp
auto s = "foobar" | replace("bar","baz");
```

Other operations may modify the value, as in the case of `sort`:

```cpp
std::vector<int> v{1,5,3,7,-22,1,10};
v | sort;
```

::: tip
This may seem odd at first, but remember: pipedream considers `|` to be a general form of `.`.  Thus, like member functions, operations may be modifying or not, and are documented as such.
:::

For operations such as `replace` that produce a new value of the same type, which may be assigned back using `|=`:

```cpp
std::string s = "abc";
s |= replace(".b", "xb");
```

### Generator Operations

Generators are, strictly speaking, operations that produce values on demand with `next()`, and may be used in range-based for.  For example:

```cpp
for(auto i : from_to(0,5))
    std::cout << i << std::endl;
```

In this case, `from_to` is a generator that produces values in the half-open range from `0` to `5`.

Some operations *consume* input from generators:

```cpp
auto v = from_to(0,5) | collect<std::vector>;
```

Note that `collect` is not a generator: it's an immediate operation that produces a `std::vector` by consuming input from a generator.  Of course, because chaining operations is *very useful*, generators can produce and consume values:

```cpp
auto v = from(0) | take(3) | collect<std::vector>;
```

In this case `take(n)` will produce the first `n` values, and then is empty.


## Getting Things Done

So, by now you have likely seen examples, and want to know what you can really *do* and *how to do it*.  For the most part, the API reference can help you here; it's organized by some broad categories, and this is a small-but-growing library.

You may also wonder how you can [[build your own]](/doc/building), which you can read about there.

Here, we will cover a few things to get you started.

### Standard Containers

You may try something like this.  It won't work:

```cpp
std::vector<int> v{1,2,3,4,5};

// Error:
auto v2 = v | take(3) | collect<std::vector>;
```

This is because `std::vector` is not a generator.  Instead, for containers, we need to "adapt" them into a generator chain.  This is done with `each`:

```cpp
std::vector<int> v{1,2,3,4,5};

// OK
auto v2 = v | each | take(3) | collect<std::vector>;
```

Vectors aren't the only container that works:

@[code](@/../../examples/basic_stdmap1.cpp)

### `collect`

One of the more "hard to put down" operations used througout the documentation is `collect<C>`:

```cpp
auto v = from_to(0,10) | collect<std::vector>;
```

This is of course very flexible and direct for constructing container values.  It too is not limited to `std::vector`; let's pull the front page example apart a bit:

```cpp
auto key_g   = "a,b,c" | split(",");
auto value_g = from(1);

auto m = zip(key_g, value_g) | collect<std::map>;
```

In this case, `collect<std::map>` specifically builds a map from the first two entries of a `std::tuple`.  This of course is exactly what `zip` generates!

But, what exactly does `zip` provide?

### `zip`

As it happens, `zip` is a "generator of a bunch of generators".  It's not limited to two inputs:

@[code](@/../../examples/basic_zip1.cpp)

This generates a `std::tuple` from each *generator* given as a parameter, which is handy for a number of things, such as the above destructuring.

You will also notice that we use two `from` generators here: these are unbounded, but we don't get an infinite loop (and a crash).  This is because `zip` only generates values until *any* of the generators are empty, then it is empty in turn.

::: tip
You may wonder, "but what if I want to iterate all the values of uneven containers, until the end of the largest?"

This is possible: you could make a generator that returned first its input then some default or empty value.  It will be implemented in pipedream as soon as I encounter a real use case.  So far after years of using similar constructs, I have not.
:::

### `erase_if` and `filter`

You are likely familiar with the [[erase-remove idiom]](https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom).  If you are like most, you find this annoying an error-prone.  Pipedream, of course, lets you simply do the following:

```cpp
auto v = from_to(0,10) | collect<std::vector>;

v | erase_if([](auto x) { return x < 5; });
```

This is a modifying operation; if you want a *copy*, you can use the `filter` generator; but note, the test is reversed:

```cpp
auto v = from_to(0,10) | collect<std::vector>;

auto v2 = v | each
  | filter([](auto x) { return !(x < 5); })
  | collect<std::vector>;
```


### Splitting and Joining Strings

These common operations should be simple; with pipedream, they are:

```cpp
auto v = "foo,bar,baz" | split(",") | join(":") | collect<std::vector>;
```

You may use a `std::regex` for split, or a regular string.

::: warning Note
`split` produces `std::string_view`.  Therefore, this makes a `std::vector<std::string_view>`.  This is normally almost certainly what you want... unless you're splitting a temporary string.
:::

If you want to make copies, you might do something like the following:

@[code](@/../../examples/basic_split1.cpp)

This is *rather* contrived, but if you don't `map_to<std::string>` here, you will end up with a vector of dangling pointers.  But this is very easy to do as we wish, instead.
