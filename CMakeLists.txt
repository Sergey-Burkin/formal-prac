cmake_minimum_required(VERSION 3.5)

project(00-start-test)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)


#include(CodeCoverage)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(start_test run_tests.cpp test.cpp test.h symbol.h symbol.cpp grammar.h grammar.cpp CYK.cpp CYK.h rule.h rule.cpp)
add_executable(runMain main.cpp symbol.h symbol.cpp grammar.h grammar.cpp CYK.cpp CYK.h rule.h rule.cpp)
target_link_libraries(start_test ${GTEST_LIBRARIES} Threads::Threads)

#setup_target_for_coverage(tests 00_start_test coverage)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
