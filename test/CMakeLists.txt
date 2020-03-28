cmake_minimum_required(VERSION 3.13)

find_package(GTest REQUIRED)
enable_testing()
file(GLOB_RECURSE test_src *_test.cpp)

set(testname stdformattests)
add_executable(${testname} ${test_src})
target_link_libraries(${testname} stdformat GTest::Main)
add_test(${testname} ${testname})
