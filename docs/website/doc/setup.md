# Setup

## Install

The source is available here:

 * <https://github.com/rpav/cpp-pipedream>

This is a header-only library; building by default will build examples.
Installation is also useful.

```sh
$ git clone https://github.com/rpav/cpp-pipedream.git
$ cd cpp-pipedream
$ mkdir build; cd build
$ cmake ..
$ make install
```

Additionally, tests and docs are possible, if Doxygen or `BUILD_TESTING` is
enabled in CMake.

## Examples and Tests

Many of the examples in this documentation are available in the `examples/` directory.  These will build by default.

Tests will not build by default, but you can enable them with `-DBUILD_TESTING=ON` as appropriate to cmake, and run with `ctest` or `make test` etc.  Tests are in `t/`.

## Project Inclusion

If you use cmake, and ran `make install` (or equivalent) you should be
able to simply pull in `pipedream` and use it.

From `examples/CMakeLists.txt`:

@[code lang=cmake transcludeWith=snip:setup](@/../../examples/CMakeLists.txt)

From `examples/setup_example.cpp`:

@[code](@/../../examples/setup_example.cpp)

Building and running this should produce the expected results:

```sh
$ cd examples
$ mkdir build; cd build
$ cmake ..
  <output>
$ make setup_example
  <output>
$ ./setup_example
1
3
5
7
9
$
```

## On Headers

To get everything from pipedream ("piped" for short):

```cpp
#include <piped.hpp>
```

However, this pulls in a number of things you may not want, such as `<regex>`, which only apply to certain operations.  You can instead pull in separate headers if you choose:

```cpp
#include <piped/string.hpp>
```

For the purposes of this documentation, examples will just `#include <piped.hpp>`.

## On Namespaces

A basic example:

```cpp
#include <vector>
#include <piped.hpp>

using namespace piped;

auto v = from_to(0,5) | collect<std::vector>
```

You are *not* required, of course, to dump this namespace entirely the global namespace.  The alternative:

```cpp
using namespace piped::operators;   // Only the definitions for operator| and |=
namespace pd = piped;

auto v = pd::from_to(0,5) | pd::collect<std::vector>
```

But for the purposes of this documentation, for brevity and clarity, I will assume we have `using namespace piped;`.
