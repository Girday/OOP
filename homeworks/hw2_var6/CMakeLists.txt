# CMakeLists.txt

cmake_minimum_required(VERSION 4.1.1 FATAL_ERROR)

project(HW1_VAR16)
set(CMAKE_CXX_STANDARD 17)


add_library(gcd src/compile/gcd.cpp)
target_include_directories(gcd PUBLIC src/include)


add_executable(HW1_VAR16 src/compile/main.cpp)
target_link_libraries(HW1_VAR16 gcd)


# GoogleTest

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_gcd src/test/basicTest.cpp)
target_link_libraries(test_gcd gcd GTest::gtest_main)

add_executable(random_test src/test/randomTest.cpp)
target_link_libraries(random_test gcd GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_gcd)
gtest_discover_tests(random_test)
