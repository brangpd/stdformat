cmake_minimum_required(VERSION 3.13)
project(stdformat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib)
add_subdirectory(test)

add_library(ATestClass ATestClass.cpp)
target_link_libraries(ATestClass stdformat)
add_executable(example main.cpp)
target_link_libraries(example stdformat ATestClass)
