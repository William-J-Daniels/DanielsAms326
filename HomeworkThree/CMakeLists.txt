cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(HomeworkThree VERSION 1.0.0)

add_executable(Hw3P1 examples/problem_one.cpp)
target_link_libraries(Hw3P1 PUBLIC LinearAlgebra)

#
#

add_executable(Hw3P3 examples/problem_three.cpp)
target_link_libraries(Hw3P3 PUBLIC OrdinaryDifferentialEquations)
target_link_libraries(Hw3P3 PUBLIC root_finding)
