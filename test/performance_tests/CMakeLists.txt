cmake_minimum_required(VERSION 3.13)

file(GLOB_RECURSE performance_test_src *_test.cpp)

include_directories(../include)
add_executable(stdformat_performance_test ${performance_test_src})
target_link_libraries(stdformat_performance_test PRIVATE stdformat GTest::Main)
add_test(stdformat_performance_test stdformat_performance_test)

find_package(benchmark)
if (benchmark_FOUND)
  add_executable(stdformat_benchmark benchmark.cpp)
  target_link_libraries(stdformat_benchmark benchmark::benchmark)
endif ()
