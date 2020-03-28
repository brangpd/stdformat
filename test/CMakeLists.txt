cmake_minimum_required(VERSION 3.13)

find_package(GTest REQUIRED)
enable_testing()
file(GLOB_RECURSE test_src *_test.cpp)
set(tests_lib)
foreach (file ${test_src})
	get_filename_component(testname ${file} NAME_WE)
	add_library(${testname} ${file})
	target_link_libraries(${testname} stdformat)
	list(APPEND tests_lib ${testname})

	add_executable(${testname}_exec ${testname})
	target_link_libraries(${testname}_exec ${testname} GTest::GTest GTest::Main)

	add_test(${testname}_exec ${testname}_exec)
endforeach ()

add_executable(all_test ${tests_lib})
target_link_libraries(all_test ${tests_lib} GTest::GTest GTest::Main stdformat)
