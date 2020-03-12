cmake_minimum_required(VERSION 3.13)
project(stdformat CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_library(stdformat format type_traits)
set_target_properties(stdformat PROPERTIES LINKER_LANGUAGE CXX)

find_package(GTest REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test GTest::Main stdformat)
