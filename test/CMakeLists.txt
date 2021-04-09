cmake_minimum_required(VERSION 3.13)

find_package(GTest)
if (GTest_FOUND)
  enable_testing()

  add_subdirectory(format_tests)
  add_subdirectory(performance_tests)
endif ()
