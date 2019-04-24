// examples/basic_zip1.cpp

#include <iostream>
#include <tuple>
#include <vector>
#include <piped.hpp>

using namespace piped;

int main()
{
    auto v = from_to(0,100) | collect<std::vector>;

    auto g = zip(from(1),
                 from(10, 5),
                 v | each);

    for(auto [a,b,c] : g) {
        std::cout << a << " "
                  << b << " "
                  << c
                  << std::endl;
    }
}
