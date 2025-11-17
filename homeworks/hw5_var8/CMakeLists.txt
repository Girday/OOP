cmake_minimum_required(VERSION 3.10)

project(HW4_VAR16
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа №4: Итераторы и аллокаторы"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(HW5_VAR8 main.cpp)
target_include_directories(HW5_VAR8 PRIVATE ${INCLUDE_DIR})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(HW5_VAR8 PRIVATE -Wall -Wextra -Wpedantic)
endif()
