cmake_minimum_required(VERSION 3.10)

# Настройка проекта
project(HW2_VAR6 
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 2: Класс Five с Правилом пяти"
    LANGUAGES CXX
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка директорий
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Поиск исходных файлов библиотеки
file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

# Создание библиотеки
add_library(FIVE ${LIBRARY_SOURCES})

# Добавление директории с заголовочными файлами
target_include_directories(FIVE PUBLIC ${INCLUDE_DIR})

# Создание основного исполняемого файла
add_executable(HW2_VAR6 main.cpp)

# Связывание библиотеки с исполняемым файлом
target_link_libraries(HW2_VAR6 PRIVATE FIVE)

# Настройка компилятора
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(FIVE PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(HW2_VAR6 PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ============== GOOGLE TEST ==============

# Включение поддержки тестирования
enable_testing()

# Включение FetchContent для автоматической загрузки Google Test
include(FetchContent)

# Загрузка Google Test из GitHub
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

# Отключаем установку gtest в систему
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)

# Делаем Google Test доступным
FetchContent_MakeAvailable(googletest)

# Создание исполняемого файла для тестов
add_executable(test_five gtests.cpp)

# Связывание тестов с библиотекой и Google Test
target_link_libraries(test_five 
    PRIVATE 
    FIVE 
    GTest::gtest_main
)

# Добавление тестов в CTest
include(GoogleTest)
gtest_discover_tests(test_five)

# Настройка компилятора для тестов
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(test_five PRIVATE -Wall -Wextra -Wpedantic)
endif()