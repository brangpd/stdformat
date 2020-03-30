cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE format_test_src *_test.cpp)

add_executable(stdformat_test ${format_test_src})
target_link_libraries(stdformat_test testutil)
add_test(stdformat_test stdformat_test)
