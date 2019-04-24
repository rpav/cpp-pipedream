#include <piped.hpp>

using namespace piped;
using namespace piped::operators;

int main()
{
    auto v0 = from_to(0, 10) | collect<std::vector>;
    auto v1 = v0 | each | map([](auto i) { return i * i; }) | collect<std::vector>;
}
