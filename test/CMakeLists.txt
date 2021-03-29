cmake_minimum_required(VERSION 3.13)

find_package(GTest)
if (GTest_FOUND)
  enable_testing()

  add_library(testutil include/testutil.h)
  target_link_libraries(testutil GTest::Main stdformat)
  target_include_directories(testutil PUBLIC include)

  add_subdirectory(format_tests)
  add_subdirectory(performance_tests)
endif ()
