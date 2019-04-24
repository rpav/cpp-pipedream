// examples/gen_chain1.cpp

#include <iostream>
#include <type_traits>
#include <piped.hpp>

using namespace piped;

template<typename G, typename F>
struct my_generator_map : public generator<my_generator_map<G, F>> {
    using input_type       = std::decay_t<G>;
    using input_value_type = typename input_type::value_type;

    using value_type  = decltype(std::declval<F>()(std::declval<input_value_type>()));
    using option_type = std::optional<value_type>;

    input_type input;
    F          function;

    option_type next()
    {
        if(auto v = input.next(); v) return function(*v);

        return std::nullopt;
    }

    bool empty() const { return input.empty(); }
};

template<typename F>
struct my_map_ {
    F function;

    template<typename G>
    inline my_generator_map<G, F> process(G&& input) const
    {
        return {{}, input, function};
    }
};

template<typename F>
my_map_<F> my_map(const F& f) { return {f}; }

int main()
{
    auto g = from_to(1, 5) | my_map([](auto v) { return v + 1; });

    for(auto i : g) { std::cout << i << std::endl; }
}
