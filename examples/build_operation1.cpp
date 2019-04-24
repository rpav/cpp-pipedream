// examples/build_operation1.cpp

#include <piped.hpp>
using namespace piped;

constexpr struct add1_ {
    int process(int i) const {
        return i + 1;
    }
} add1;

int main() {
    return 1 | add1;
}
