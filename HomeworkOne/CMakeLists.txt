cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(HomeworkOne VERSION 1.0.0)

add_executable(Hw1P1 examples/ProblemOne.cpp)
target_link_libraries(Hw1P1 PUBLIC root_finding)
