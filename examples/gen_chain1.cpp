// examples/gen_chain1.cpp

#include <iostream>
#include <piped.hpp>
using namespace piped;

template<typename G, typename T>
struct generator_add : public generator<generator_add<G, T>> {
    using input_type = std::decay_t<G>;

    using value_type  = T;
    using option_type = std::optional<T>;

    input_type input;
    T          v{0};

    option_type next()
    {
        if(auto i = input.next(); i)
            return {*i + v};

        return std::nullopt;
    }

    bool empty() const { return input.empty(); }
};

template<typename T>
struct add_ {
    const T v{1};

    template<typename G>
    generator_add<G, T> process(G&& g) const
    {
        return {{}, g, v};
    }
};

template<typename T>
add_<T> add(T n) { return {n}; }

int main()
{
    auto v = from_to(0, 10) | collect<std::vector>;
    auto g = v | each | add(5);

    for(auto i : g)
        std::cout << i << std::endl;
}
