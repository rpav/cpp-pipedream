#snip:setup
cmake_minimum_required(VERSION 3.11)
project(pipedream_examples)

set(CMAKE_CXX_STANDARD 17)

#find_package(pipedream REQUIRED)

add_executable(setup_example setup_example.cpp)
target_link_libraries(setup_example
    PRIVATE pipedream)

#snip:setup

add_executable(test1 test.cpp)
target_link_libraries(test1
  PRIVATE pipedream)


add_executable(basic_stdmap1 basic_stdmap1.cpp)
target_link_libraries(basic_stdmap1 PRIVATE pipedream)

add_executable(basic_zip1 basic_zip1.cpp)
target_link_libraries(basic_zip1 PRIVATE pipedream)

add_executable(basic_split1 basic_split1.cpp)
target_link_libraries(basic_split1 PRIVATE pipedream)


add_executable(build_operation1 build_operation1.cpp)
target_link_libraries(build_operation1 PRIVATE pipedream)

add_executable(build_operation2 build_operation2.cpp)
target_link_libraries(build_operation2 PRIVATE pipedream)

add_executable(build_operation3 build_operation3.cpp)
target_link_libraries(build_operation3 PRIVATE pipedream)


add_executable(gen_simple1 gen_simple1.cpp)
target_link_libraries(gen_simple1 PRIVATE pipedream)

add_executable(gen_chain1 gen_chain1.cpp)
target_link_libraries(gen_chain1 PRIVATE pipedream)
