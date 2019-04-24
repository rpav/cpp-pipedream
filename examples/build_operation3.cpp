// examples/build_operation3.cpp

#include <iostream>
#include <piped.hpp>
using namespace piped;

template<typename T>
struct add_ {
    const T v{1};

    T process(T i) const { return i + v; }
};

template<typename T>
add_<T> add(T n) { return {n}; }

int main()
{
    auto i = 1 | add(2) | add(3);
    auto f = 1.0f | add(0.5f);

    std::cout << i << " " << f << std::endl;
}
