cmake_minimum_required(VERSION 3.10)

project(LAB3_VAR3
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа №3: Наследование и Полиморфизм"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
list(FILTER LIBRARY_SOURCES EXCLUDE REGEX ".*main.cpp$")

add_library(GEOMETRY ${LIBRARY_SOURCES})

target_include_directories(GEOMETRY PUBLIC ${INCLUDE_DIR})

add_executable(LAB3_VAR3 ${SOURCE_DIR}/main.cpp)

target_link_libraries(LAB3_VAR3 PRIVATE GEOMETRY)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(GEOMETRY PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(LAB3_VAR3 PRIVATE -Wall -Wextra -Wpedantic)
endif()


# ============== GOOGLE TEST ==============

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(gtests tests.cpp)

target_link_libraries(gtests PRIVATE GEOMETRY GTest::gtest_main)

target_include_directories(gtests PRIVATE ${INCLUDE_DIR} ${gtest_SOURCE_DIR}/googletest/include)

include(GoogleTest)
gtest_discover_tests(gtests)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(gtests PRIVATE -Wall -Wextra -Wpedantic)
endif()