// examples/build_operation2.cpp

#include <iostream>
#include <piped.hpp>
using namespace piped;

constexpr struct add_ {
    const int v{1};

    int process(int i) const { return i + v; }

    add_ operator()(int n) const { return {n}; }
} add;

int main()
{
    auto a = 1 | add;
    auto b = 1 | add(2);

    std::cout << a << " " << b << std::endl;
}
