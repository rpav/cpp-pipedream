// examples/gen_simple1.cpp

#include <iostream>
#include <piped.hpp>

using namespace piped;

template<typename T>
struct generator_from : public generator<generator_from<T>> {
    using value_type  = T;
    using option_type = std::optional<T>;

    T       cur{};
    const T incr{1};

    option_type next()
    {
        auto v = cur;
        cur += incr;
        return v;
    }
    bool empty() const { return false; }
};

template<typename T>
inline generator_from<T> my_from(T n, T by = T{1})
{
    return {{}, n, by};
}

int main()
{
    for(auto i : my_from(1)) {
        std::cout << i << std::endl;
        if(i > 5) break;
    }
}
