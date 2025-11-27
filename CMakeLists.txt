cmake_minimum_required(VERSION 3.10)
project(OOP_2)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(
    main 
    main.cpp 
    twelve.cpp
)

enable_testing()

add_executable(
    tests 
    tests.cpp 
    twelve.cpp
)

target_link_libraries(
    tests
    GTest::gtest
    GTest::gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(tests)