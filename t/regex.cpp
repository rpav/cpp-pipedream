#include <string>

#include <piped.hpp>

#include "catch.hpp"

using namespace piped;
using namespace piped::operators;
using namespace piped::literals::regex;

TEST_CASE("piped_regex_replace", "[piped][regex]")
{
    std::string s  = "abc";
    auto        s1 = s | replace(".b"_re, "xb");

    REQUIRE(s1 == "xbc");
    REQUIRE(s == "abc");

    s |= replace(".b"_re, "xb");
    REQUIRE(s == "xbc");
}

TEST_CASE("piped_each_match", "[piped][each][regex]")
{
    std::string s = "X:Y:Z:";
    auto        g = s | each_match(".:"_re);

    REQUIRE(g.next()->str() == "X:");
    REQUIRE(g.next()->str() == "Y:");
    REQUIRE(g.next()->str() == "Z:");
    REQUIRE(g.empty());

    auto v = s | each_match(".:"_re) | map_nth(0)
             | map_to<std::string_view> | collect<std::vector>;
    REQUIRE(std::is_same_v<decltype(v), std::vector<std::string_view>>);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == "X:");
    REQUIRE(v[1] == "Y:");
    REQUIRE(v[2] == "Z:");
}

TEST_CASE("piped_split_regex", "[piped][split][regex]")
{
    auto s = "a:,b`,c" | split(".,"_re) | join(":");

    REQUIRE(std::is_same_v<decltype(s), std::string>);
    REQUIRE(s == "a:b:c");
}
