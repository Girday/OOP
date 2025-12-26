cmake_minimum_required(VERSION 3.10)

project(HW5_VAR8
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа №5: Итераторы и аллокаторы"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
add_library(MyLibrary ${LIBRARY_SOURCES})
target_include_directories(MyLibrary PUBLIC ${INCLUDE_DIR})

add_executable(HW5_VAR8 main.cpp)
target_link_libraries(HW5_VAR8 PRIVATE MyLibrary)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(MyLibrary PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(HW5_VAR8 PRIVATE -Wall -Wextra -Wpedantic)
endif()


# GoogleTest

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(gtests tests.cpp)
target_include_directories(gtests PRIVATE ${INCLUDE_DIR})

target_link_libraries(gtests PRIVATE GTest::gtest_main MyLibrary)

include(GoogleTest)
gtest_discover_tests(gtests)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(gtests PRIVATE -Wall -Wextra -Wpedantic)
endif()