cmake_minimum_required(VERSION 3.15)
project(KitsFinderProject LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Пути к заголовкам
include_directories(${CMAKE_SOURCE_DIR}/include)

# Автоматически собираем все cpp-файлы
file(GLOB SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/main.cpp"
)

# Создаём исполняемый файл
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Настройки вывода бинарников
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Настройка флагов компиляции в зависимости от компилятора
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message(STATUS "Компилятор: GCC")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -finput-charset=UTF-8 -fexec-charset=UTF-8)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Компилятор: Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -finput-charset=UTF-8 -fexec-charset=UTF-8)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(STATUS "Компилятор: MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /utf-8)
endif()

# На Windows добавить .exe (опционально)
if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".exe")
endif()