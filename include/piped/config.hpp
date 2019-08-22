#pragma once

/**
  @file
  @brief Compile-derived configuration values.
 */

namespace piped {

/// Configuration value namespace
namespace config {

/// Values based on `#define` or -D
namespace defined{};

#ifndef NDEBUG
constexpr bool isDebug = true;
#else
constexpr bool isDebug = false;
#endif

#ifdef PIPED_PTR_ALWAYS_CHECK
namespace defined { constexpr bool ptrAlwaysCheck = true; }
#else
namespace defined { constexpr bool ptrAlwaysCheck = false; }
#endif

constexpr bool ptrCheck = (isDebug || defined::ptrAlwaysCheck);

}

}
