cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(AMS326 VERSION 1.0.0)

# libraries (roughly corresponds to lectures)
add_subdirectory(RandomNumbers)
#add_subdirectory(ParallelComputing)
add_subdirectory(LinearAlgebra)
add_subdirectory(Differentiation)
add_subdirectory(Integration)
add_subdirectory(RootFinding)
add_subdirectory(Interpolation)

# homeworks
add_subdirectory(HomeworkOne)
add_subdirectory(HomeworkTwo)

# exams
add_subdirectory(ExamOne)
