#include <iostream>
#include <piped.hpp>

//using namespace piped;              // Useful, or you can alias
namespace pd = piped;
using namespace piped::operators;

int main() {
    auto g = pd::from_to(1,10) | pd::filter([](auto i) { return i % 2; });

    for(auto i : g)
        std::cout << i << std::endl;
}
