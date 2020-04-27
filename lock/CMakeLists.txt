cmake_minimum_required(VERSION 3.16.3)

project(Lock)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

enable_testing()

set(TEST_SRC
    main.cpp
)

add_executable(LockTest ${TEST_SRC})

add_test(
    NAME LockTest
    COMMAND LockTest
)
