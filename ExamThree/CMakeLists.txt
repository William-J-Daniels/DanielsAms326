cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ExamThree VERSION 1.0.0)

add_executable(Exam3P examples/problem.cpp)
target_link_libraries(Exam3P PUBLIC OrdinaryDifferentialEquations)
target_link_libraries(Exam3P PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(Exam3P PUBLIC TBB::tbb)
