# This sets up appropriate warnings and some flag tweaks to build correctly
#
# -std= and /std: now handled by cxx_features.cmake
# -lc++abi should be handled by conan?

# reset these in case of from-cmake config

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(gnu_cxx_warnings "-W -Wall -Wextra -Wno-unused-label -Wno-unused-parameter")
set(gnu_cxx_warn_error "-Werror=return-type -Werror=unused-result")

set(clang_cxx_warnings "-W -Wall -Wextra")
set(clang_cxx_warn_error "-pedantic-errors -Werror=return-type -Werror=unused-result")
set(clang_cxx_nowarn "-Wno-unused-parameter -Wno-gnu-anonymous-struct -Wno-nested-anon-types -Wno-unused-label")

message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if (WIN32 AND NOT MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /permissive-")
  else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${clang_cxx_warnings} ${clang_cxx_warn_error} ${clang_cxx_nowarn}")
  endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${gnu_cxx_warnings} ${gnu_cxx_warn_error}")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG /MDd /Zi /D_ITERATOR_DEBUG_LEVEL=0 /GL")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /GL")

  set(all_linker_flags "/LTCG")

  set(CMAKE_MODULE_LINKER_FLAGS "${all_linker_flags}")
  set(CMAKE_SHARED_LINKER_FLAGS "${all_linker_flags}")
  set(CMAKE_STATIC_LINKER_FLAGS "${all_linker_flags}")
  set(CMAKE_EXE_LINKER_FLAGS "${all_linker_flags}")

  set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "")
  set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "")
  set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/DEBUG")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /permissive-")
endif ()

function(FlagReport)
  message("**   C++ flags: ${CMAKE_CXX_FLAGS}")
  message("**   C++ debug    flags: ${CMAKE_CXX_FLAGS_DEBUG}")
  message("**   C++ rwdi     flags: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  message("**   C++ release  flags: ${CMAKE_CXX_FLAGS_RELEASE}")
  message("**   Link flags: ${CMAKE_EXE_LINKER_FLAGS}")
  message("**   Link debug flags: ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
  message("**")
  message("**   This build: ${CMAKE_BUILD_TYPE}")
endfunction(FlagReport)
