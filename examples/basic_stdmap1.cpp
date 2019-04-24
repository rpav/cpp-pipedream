// examples/basic_stdmap1.cpp

#include <iostream>
#include <map>
#include <string>
#include <piped.hpp>

using namespace piped;

int main() {
    std::map<std::string, std::string> m{{"foo", "oof"}, {"bar", "rab"}, {"baz", "zab"}};

    for(auto p : m | each | take(2)) {
        std::cout << p.second << std::endl;
    }
}
