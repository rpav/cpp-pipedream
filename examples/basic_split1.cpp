// examples/basic_split1.cpp

#include <iostream>
#include <string>
#include <piped.hpp>

using namespace piped;

int main()
{
    auto v = "foo,bar,baz:quux"
        | split(",")
        | join(":")
        | split(":")
        | map_to<std::string>
        | collect<std::vector>;

    for(auto&& s : v)
        std::cout << s << std::endl;
}
