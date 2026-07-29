cmake_minimum_required(VERSION 3.25)

project(
    Dominus
    VERSION 0.1.0
    DESCRIPTION "Reference implementation of the Dominus programming language"
    LANGUAGES CXX
)

include(CTest)

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

include(DominusWarnings)
include(DominusSanitizers)

add_library(dominus_core STATIC
    src/dominus_core.cpp
    src/source/source_location.cpp
    src/source/source_manager.cpp
    src/source/source_span.cpp
)

target_include_directories(dominus_core
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features(dominus_core
    PUBLIC
        cxx_std_23
)

set_target_properties(dominus_core PROPERTIES
    CXX_EXTENSIONS OFF
)

dominus_enable_warnings(dominus_core)
dominus_enable_sanitizers(dominus_core)

add_executable(dominus
    tools/dominus/main.cpp
)

target_link_libraries(dominus
    PRIVATE
        dominus_core
)

set_target_properties(dominus PROPERTIES
    CXX_EXTENSIONS OFF
)

dominus_enable_warnings(dominus)
dominus_enable_sanitizers(dominus)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.5.3
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(doctest)

    include("${DOCTEST_CMAKE_HELPER}")

    add_executable(dominus_tests
        tests/test_harness.cpp
        tests/source/source_manager_tests.cpp
        tests/source/source_span_tests.cpp
    )

    target_link_libraries(dominus_tests
        PRIVATE
            dominus_core
            doctest::doctest_with_main
    )

    set_target_properties(dominus_tests PROPERTIES
        CXX_EXTENSIONS OFF
    )

    dominus_enable_warnings(dominus_tests)
    dominus_enable_sanitizers(dominus_tests)

    doctest_discover_tests(dominus_tests)
endif()
