cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE performance_test_src *_test.cpp)

add_executable(stdformat_performance_test ${performance_test_src})
target_link_libraries(stdformat_performance_test testutil)
add_test(stdformat_performance_test stdformat_performance_test)
