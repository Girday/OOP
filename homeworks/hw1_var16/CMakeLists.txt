cmake_minimum_required(VERSION 4.1.1 FATAL_ERROR) # минимальная версия CMake

project(HW1_VAR16) # название проекта

add_library(gcd src/compile/gcd.cpp src/include/gcd.h)
add_executable(HW1_VAR16 src/compile/main.cpp)
target_link_libraries(HW1_VAR16 gcd)

# -----------------------------
# GoogleTest через FetchContent
# -----------------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# Эта опция нужна, чтобы отключить установку gtest в систему
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_gcd src/test/gtest.cpp)
target_link_libraries(test_gcd gcd GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_gcd)