cmake_minimum_required(VERSION 3.10)

project(HW6_VAR6
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа №6: Паттерны проектирования"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HW6_VAR6 
    main.cpp
    objects/npc/npc.cpp
    objects/bandit/bandit.cpp
    objects/bear/bear.cpp
    objects/elf/elf.cpp
)

target_include_directories(HW6_VAR6 PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/npc
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/bandit
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/bear
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/elf
)

if (CMAKE_CXX_COMPLIER_ID STREQUAL "GNU")
    target_compile_options(HW6_VAR6 PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
