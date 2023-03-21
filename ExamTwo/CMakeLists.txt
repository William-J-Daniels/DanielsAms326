cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ExamOne VERSION 1.0.0)

add_executable(Exam2P1 examples/problem_one.cpp)
target_link_libraries(Exam2P1 PUBLIC Integration)
