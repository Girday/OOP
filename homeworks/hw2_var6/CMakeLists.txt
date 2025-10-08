# CMakeLists.txt для лабораторной работы 2
# Демонстрирует современную организацию проекта с разделением на библиотеку и исполняемый файл

cmake_minimum_required(VERSION 3.10)

# Настройка проекта
project(HW2_VAR6 
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 2: Класс DashArray с Правилом пяти"
    LANGUAGES CXX
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)  # Изменено с 20 на 11 для совместимости
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

# Создание исполняемого файла
add_executable(HW2_VAR6 main.cpp)

# Связывание библиотеки с исполняемым файлом
target_link_libraries(HW2_VAR6 PRIVATE FIVE)

# Настройка компилятора (опционально)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(FIVE PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(HW2_VAR6 PRIVATE -Wall -Wextra -Wpedantic)
endif()