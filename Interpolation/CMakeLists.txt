cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Interpolation VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
  include/polynomialinterpolator.h
  include/linear.h
)
target_link_libraries(${PROJECT_NAME} PUBLIC LinearAlgebra)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/polynomialinterpolator.h
  include/linear.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEARER "${public_headers}")
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
# since i used template classes i cant separate into header and implimentation file
# therefore cmake cannot deduce the language

add_executable(linear_interpolation_example examples/linear_interpolation_example.cpp)
target_link_libraries(linear_interpolation_example PUBLIC ${PROJECT_NAME})
