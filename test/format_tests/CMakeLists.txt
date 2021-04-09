cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE format_test_src *_test.cpp)

include_directories(stdformat_test ../include)
add_executable(stdformat_test ${format_test_src})
target_link_libraries(stdformat_test PRIVATE stdformat GTest::Main)
add_test(stdformat_test stdformat_test)
