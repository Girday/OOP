cmake_minimum_required(VERSION 3.10)

project(HW6_VAR6
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа №6: Паттерны проектирования"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(npc npc.cpp npc.h)
target_include_directories(npc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(bandit bandit.cpp bandit.h)
target_include_directories(bandit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bandit PUBLIC npc)

add_library(bear bear.cpp bear.h)
target_include_directories(bear PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bear PUBLIC npc)

add_library(elf elf.cpp elf.h)
target_include_directories(elf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(elf PUBLIC npc)

add_executable(HW6_VAR6 main.cpp)
target_link_libraries(HW6_VAR6 PRIVATE bandit bear elf npc)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(npc PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(bandit PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(bear PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(elf PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(HW6_VAR6 PRIVATE -Wall -Wextra -Wpedantic)
endif()
