cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ExamOne VERSION 1.0.0)

add_executable(F1 examples/prob_one.cpp)
target_link_libraries(F1 PUBLIC random_numbers)
target_link_libraries(F1 PUBLIC OpenMP::OpenMP_CXX)

add_executable(F2 examples/prob_two.cpp)

add_executable(F3 examples/prob_three.cpp)
target_link_libraries(F3 PUBLIC OrdinaryDifferentialEquations)
