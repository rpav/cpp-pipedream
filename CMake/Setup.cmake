set(ENABLE_SANITIZER "" CACHE STRING "Build with sanitizer")
set_property(CACHE ENABLE_SANITIZER PROPERTY STRINGS "" address undefined address,undefined)
set(CXX_STDLIB "libstdc++" CACHE STRING "Which std implementation to use")

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(gnu_cxx_warnings "-Wall -Wextra -Wno-unused-parameter")
set(gnu_cxx_warn_error "-Werror=return-type -Werror=unused-result")

set(clang_cxx_warnings "-Wall -Wextra -Wno-unused-parameter")
set(clang_cxx_warn_error "-pedantic-errors -Werror=return-type -Werror=unused-result")
set(clang_cxx_nowarn "-Wno-unused-parameter -Wno-gnu-anonymous-struct -Wno-nested-anon-types")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(X64 1)
  set(ARCH "x64")
else ()
  set(X86 1)
  set(ARCH "x86")
endif ()

message(STATUS "Architecture: ${ARCH}")

if (WIN32)
  message(STATUS "Building for Win32-${ARCH}")

  if (ENABLE_SANITIZER)
    message(WARNING "ENABLE_SANITIZER specified, but Address Sanitizer not supported in Windows")
  endif ()
else ()
  message(STATUS "Building for Linux-${ARCH}")

  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=lld")

  if (ENABLE_SANITIZER)
    message(STATUS "Sanitizer(s) enabled: ${ENABLE_SANITIZER}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=${ENABLE_SANITIZER}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=${ENABLE_SANITIZER}")
  endif ()

  if (ENABLE_GPROF)
    message(STATUS "Enabling profiling (via gprof)")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
  endif ()
endif ()

message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if (WIN32 AND NOT MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /EHsc /permissive-")
    set(locallib msvc)
  else ()
    if (CXX_STDLIB STREQUAL "libc++")
      message(STATUS "Using libc++")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++ -lc++abi")
    else ()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
    endif ()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${clang_cxx_warnings} ${clang_cxx_warn_error} ${clang_cxx_nowarn}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fno-omit-frame-pointer -ggdb")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

    set(locallib gnu)
  endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ${gnu_cxx_warnings} ${gnu_cxx_warn_error}")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

  set(locallib gnu)
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

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /EHsc /permissive-")
  set(locallib msvc)
endif ()

if(locallib STREQUAL "")
  message(FATAL_ERROR "Could not determine library type for ${CMAKE_CXX_COMPILER_ID}")
endif()

list(INSERT CMAKE_INCLUDE_PATH 0 ${CMAKE_SOURCE_DIR}/lib/${locallib}/include)
list(INSERT CMAKE_LIBRARY_PATH 0 ${CMAKE_SOURCE_DIR}/lib/${locallib}/lib/x64)
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/lib/${locallib}/include")
link_directories("${CMAKE_SOURCE_DIR}/lib/${locallib}/lib/x64")

include(cxx_features)
include(GenerateExportHeader)

function(SetupPost)
    if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
        message("**   C++ flags: ${CMAKE_CXX_FLAGS}")
        message("**   C++ debug    flags: ${CMAKE_CXX_FLAGS_DEBUG}")
        message("**   C++ rwdi     flags: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
        message("**   C++ release  flags: ${CMAKE_CXX_FLAGS_RELEASE}")
        message("**   Link flags: ${CMAKE_EXE_LINKER_FLAGS}")
        message("**   Link debug flags: ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
        message("**   Local libraries: ${locallib}")
        message("**")
        message("**   This build: ${CMAKE_BUILD_TYPE}")
    endif()
endfunction(SetupPost)
