include(CMakePackageConfigHelpers)
configure_package_config_file(pipedreamConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfig.cmake
    INSTALL_DESTINATION ${INSTALL_LIB_DIR}/pipedream/cmake
    PATH_VARS INSTALL_INCLUDE_DIR
    )

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfigVersion.cmake
    VERSION 0.1
    COMPATIBILITY SameMajorVersion
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
    ${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/pipedreamConfigVersion.cmake
    DESTINATION
    ${INSTALL_LIB_DIR}/pipedream/cmake)

