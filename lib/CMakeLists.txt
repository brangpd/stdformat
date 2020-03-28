cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)
add_library(stdformat
		include/format src/__format.cpp
		include/charconv src/__charconv.cpp
		)
set_target_properties(stdformat PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(stdformat PUBLIC include)
