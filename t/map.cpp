#include <string>

#include <piped.hpp>

#include "catch.hpp"

using namespace piped;

TEST_CASE("piped_map_basic", "[piped][map]")
{
    auto g = from_to(0, 2) | map([](auto v) { return 1 + v; });

    REQUIRE(*g.next() == 1);
    REQUIRE(*g.next() == 2);
    REQUIRE(g.empty());
}

TEST_CASE("piped_filter_basic", "[piped][filter]")
{
    auto g = from_to(0, 10) | filter([](auto v) { return v < 2 || v >= 8; });

    REQUIRE(*g.next() == 0);
    REQUIRE(*g.next() == 1);
    REQUIRE(*g.next() == 8);
    REQUIRE(*g.next() == 9);
    REQUIRE(g.empty());
}
