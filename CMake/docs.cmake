find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_LAYOUT_FILE ${PROJECT_SOURCE_DIR}/docs/DoxygenLayout.xml)
    doxygen_add_docs(
        pipedream_docs
        ${PROJECT_SOURCE_DIR}/README.md
        ${PROJECT_SOURCE_DIR}/docs
        ${PROJECT_SOURCE_DIR}/include
        )
else()
    message(STATUS "Doxygen not found; documentation won't generate for cpp-pipedream")
endif()
