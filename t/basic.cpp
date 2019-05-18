#include <iostream>
#include <vector>

#include "catch.hpp"
#include <piped.hpp>

using namespace piped;
using namespace piped::operators;

TEST_CASE("piped_each_basic", "[piped][each]")
{
    std::vector<int> v{1, 2, 3};
    auto             g = v | each;

    REQUIRE(*g.next() == 1);
    REQUIRE(*g.next() == 2);
    REQUIRE(*g.next() == 3);
    REQUIRE(g.next() == nullptr);
    REQUIRE(g.empty());
}

TEST_CASE("piped_each_iter", "[piped][each]")
{
    std::vector<int> v{1, 2, 3};
    auto             g = v | each;

    auto b = g.begin();
    auto e = g.end();

    REQUIRE(*b == 1);
    ++b;
    REQUIRE(b != e);

    REQUIRE(*b == 2);
    ++b;
    REQUIRE(b != e);

    REQUIRE(*b == 3);
    ++b;
    REQUIRE(!(b != e));
    REQUIRE(b == e);
}

TEST_CASE("piped_seq_basic", "[piped][seq]")
{
    auto g = from_to(2, 5);

    REQUIRE(*g.next() == 2);
    REQUIRE(*g.next() == 3);
    REQUIRE(*g.next() == 4);
    REQUIRE(g.empty());
}

TEST_CASE("piped_take_basic", "[piped][take]")
{
    std::vector<int> v{1, 2, 3};
    auto             g = v | each | take(2);

    REQUIRE(*g.next() == 1);
    REQUIRE(*g.next() == 2);
    REQUIRE(g.next() == nullptr);
    REQUIRE(g.empty());
}

TEST_CASE("piped_skip_basic", "[piped][skip][collect]")
{
    auto v = from_to(1, 5) | skip(2) | collect<std::vector>;

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 3);
    REQUIRE(v[1] == 4);

    auto g = from_to(0, 4) | skip(2);
    REQUIRE(*g.next() == 2);
    REQUIRE(*g.next() == 3);
    REQUIRE(g.empty());

    auto g1 = from_to(0, 4) | skip(4);
    REQUIRE(g1.empty());

    auto g2 = from_to(10, 20) | skip(100);
    REQUIRE(g2.empty());
}

TEST_CASE("piped_collect_basic", "[piped][collect]")
{
    std::vector<int> v{1, 2, 3, 4, 5};
    auto             v1 = v | each | take(2) | collect<std::vector>;

    REQUIRE(&v != &v1);
    REQUIRE(v1.size() == 2);
    REQUIRE(v1[0] == 1);
    REQUIRE(v1[1] == 2);
    REQUIRE(std::is_same_v<decltype(v), decltype(v1)>);
}

TEST_CASE("piped_erase_basic", "[piped][erase_if]")
{
    auto v = from_to(0, 10) | collect<std::vector>;
    v | erase_if([](auto v) { return v > 1; });

    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);
}

TEST_CASE("pipe_split_basic", "[piped][string][split]")
{
    auto v = "a,b,c" | split(",") | collect<std::vector>;

    REQUIRE(std::is_same_v<decltype(v), std::vector<std::string_view>>);
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == "a");
    REQUIRE(v[1] == "b");
    REQUIRE(v[2] == "c");

    auto g   = "a,b,c" | split(",");
    auto it  = g.begin();
    auto end = g.end();

    REQUIRE(it != end);
    REQUIRE(*it == "a");
    ++it;
    REQUIRE(*it == "b");
    ++it;
    REQUIRE(*it == "c");
    ++it;
    REQUIRE(it == end);
}

TEST_CASE("pipe_collect_map_basic", "[piped][collect][std_map]") {
    auto m = zip("a,b,c" | split(","), from(1)) | collect<std::map>;

    REQUIRE(std::is_same_v<std::map<std::string_view,int>, decltype(m)>);
    REQUIRE(m.find("a") != m.end());
    REQUIRE(m.find("b") != m.end());
    REQUIRE(m.find("c") != m.end());

    REQUIRE(m.find("b")->second == 2);
}

TEST_CASE("pipe_difference_basic", "[piped][difference][std_vector]") {
    auto v1 = from_to(0,3) | collect<std::vector>;
    auto v2 = from_to(1,4) | collect<std::vector>;

    auto rv = v1 | difference(v2);

    REQUIRE(rv.size() == 2);
    REQUIRE(rv[0] == 0);
    REQUIRE(rv[1] == 3);
}
