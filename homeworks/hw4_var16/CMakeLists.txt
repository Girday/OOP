cmake_minimum_required(VERSION 3.10)

project(HW4_VAR16
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа №3: Основы метапрограммирования"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE LIBRARY_SOURCES ${SOURCE_DIR}/*.cpp)

add_library(GEOMETRY ${LIBRARY_SOURCES})
target_include_directories(GEOMETRY PUBLIC ${INCLUDE_DIR})

add_executable(HW4_VAR16 main.cpp)
target_link_libraries(HW4_VAR16 PRIVATE GEOMETRY)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(GEOMETRY PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(HW4_VAR16 PRIVATE -Wall -Wextra -Wpedantic)
endif()
