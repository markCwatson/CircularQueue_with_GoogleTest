cmake_minimum_required(VERSION 3.23)

set(This cqueue_test)

set(Sources
    cqueue_test.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC 
    gtest_main
    CircularQueue_with_GoogleTest
)

add_test(
    NAME ${This}
    COMMAND ${This}
)