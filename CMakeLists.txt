cmake_minimum_required(VERSION 3.8)

set(lib_name PocoCppBooster)
project(${lib_name} CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(Poco REQUIRED Foundation Util)

# librarry.
file(GLOB_RECURSE sources
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cxx
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cc
    )
add_library(${lib_name} SHARED ${sources})

target_include_directories(
    ${lib_name}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    ${lib_name}
    PUBLIC
    Poco::Util
    Poco::Foundation
)

# unit tests of the library.
get_directory_property(has_parent PARENT_DIRECTORY)
if(has_parent)
    set(utest_build "${lib_name}_buidl_utest")
    set(utest_run "${lib_name}_utest")
else()
    set(utest_build "buidl_utest")
    set(utest_run "utest")
endif()

file(GLOB_RECURSE utest_sources
    ${CMAKE_CURRENT_LIST_DIR}/test/src/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/test/src/*.cxx
    ${CMAKE_CURRENT_LIST_DIR}/test/src/*.cc
    )

add_executable(${utest_build} ${utest_sources})

find_package(GTest REQUIRED)

target_link_libraries(
    ${utest_build}
    PUBLIC
    ${lib_name}
    PRIVATE
    GTest::GTest
)

add_test( ${utest_run}
    COMMAND "${utest_build}" --gtest_output=xml:$<TARGET_DIR:"${utest_build}">/unit_test_result.xml
)