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

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(LAB3_VAR3 ${SOURCES})

target_include_directories(LAB3_VAR3 PUBLIC ${INCLUDE_DIR})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(LAB3_VAR3 PRIVATE -Wall -Wextra -Wpedantic)
endif()
