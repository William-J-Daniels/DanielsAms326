cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(AMS326 VERSION 1.0.0)

find_package(Threads REQUIRED)
find_package(TBB REQUIRED)
find_package(OpenMP REQUIRED)

option(debugging "Compiler settings for debugging" OFF)
option(performance "Compiler settings for performance" ON)

if(debugging)
  add_compile_options(-Wall)
  add_compile_options(-fsanitize=address)
  link_libraries(-fsanitize=address)
endif()

if(performance)
  add_compile_options(-O3)
endif()

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
add_subdirectory(HomeworkThree)

# exams
add_subdirectory(ExamOne)
add_subdirectory(ExamTwo)
