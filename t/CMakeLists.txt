enable_testing()

add_executable(pipedream_core_tests
  catchmain.cpp
  basic.cpp
  regex.cpp
  map.cpp
)
target_cxx_std(pipedream_core_tests 17)
target_link_libraries(pipedream_core_tests PRIVATE
  pipedream
  )

add_test(NAME test_pipedream_core COMMAND pipedream_core_tests)
