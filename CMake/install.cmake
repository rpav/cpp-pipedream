include(CMakePackageConfigHelpers)

configure_file(pipedreamConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfig.cmake
  @ONLY
  )

message(STATUS "Install Prefix: ${CMAKE_INSTALL_PREFIX}")

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfigVersion.cmake
  VERSION 0.1
  COMPATIBILITY SameMajorVersion
  )

install(TARGETS pipedream EXPORT pipedreamTargets
  INCLUDES DESTINATION include
  )

export(EXPORT pipedreamTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/pipedreamTargets.cmake"
  )

install(EXPORT pipedreamTargets
  FILE pipedreamTargets.cmake
  DESTINATION lib/cmake/pipedream
  )

file(GLOB PIPEDREAM_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
  )
file(GLOB PIPEDREAM_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/piped
  )

install(FILES ${PIPEDREAM_FILES} DESTINATION ${INSTALL_INCLUDE_DIR})
install(DIRECTORY ${PIPEDREAM_DIRS} DESTINATION ${INSTALL_INCLUDE_DIR})
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfigVersion.cmake"
  DESTINATION "lib/cmake/pipedream")
