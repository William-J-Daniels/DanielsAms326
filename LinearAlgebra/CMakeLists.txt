cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(LinearAlgebra VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
  include/matrix.h
)
target_link_libraries(${PROJECT_NAME} PUBLIC random_numbers)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/matrix.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEARER "${public_headers}")
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_executable(matrix_testing examples/matrix_testing.cpp)
target_link_libraries(matrix_testing PUBLIC ${PROJECT_NAME})
