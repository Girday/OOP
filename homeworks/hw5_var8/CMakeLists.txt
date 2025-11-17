cmake_minimum_required(VERSION 3.10)

project(HW4_VAR16
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа №5: Итераторы и аллокаторы"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)
add_library(FixedBlockLib ${LIBRARY_SOURCES})
target_include_directories(FixedBlockLib PUBLIC ${INCLUDE_DIR})

add_executable(HW5_VAR8 main.cpp)
target_link_libraries(HW5_VAR8 PRIVATE FixedBlockLib)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(FixedBlockLib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(HW5_VAR8 PRIVATE -Wall -Wextra -Wpedantic)
endif()
