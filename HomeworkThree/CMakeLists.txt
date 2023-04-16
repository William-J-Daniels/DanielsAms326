cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(HomeworkThree VERSION 1.0.0)

add_executable(Hw3P1 examples/problem_one.cpp)
target_link_libraries(Hw3P1 PUBLIC LinearAlgebra)

add_library(${PROJECT_NAME} SHARED
  include/prob_two.h
)
target_link_libraries(${PROJECT_NAME} PUBLIC TBB::tbb)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/prob_two.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

add_executable(Hw3P2 examples/problem_two.cpp)
target_link_libraries(Hw3P2 PUBLIC ${PROJECT_NAME})

add_executable(Hw3P3 examples/problem_three.cpp)
target_link_libraries(Hw3P3 PUBLIC OrdinaryDifferentialEquations)
target_link_libraries(Hw3P3 PUBLIC root_finding)
