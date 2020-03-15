cmake_minimum_required(VERSION 3.13)
project(stdformat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_library(stdformat
		format
		charconv __charconv.cpp
		chrono)
set_target_properties(stdformat PROPERTIES LINKER_LANGUAGE CXX)

find_package(GTest REQUIRED)
enable_testing()
add_executable(format_test format_test.cpp)
add_test(format_test format_test)
target_link_libraries(format_test GTest::Main stdformat)
