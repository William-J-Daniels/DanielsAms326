cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(OrdinaryDifferentialEquations VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
  include/odesolver.h
  src/odesolver.cpp
  include/explicitodesolver.h
  src/explicitodesolver.cpp
  include/euler.h
  src/euler.cpp
  include/eulercromer.h
  src/eulercromer.cpp
  include/midpoint.h
  src/midpoint.cpp
  include/huen.h
  src/huen.cpp
  include/implicitodesolver.h
  src/implicitodesolver.cpp
  include/ieuler.h
  src/ieuler.cpp
  include/ieulercromer.h
  src/ieulercromer.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC root_finding)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/odesolver.h
  include/explicitodesolver.h
  include/euler.h
  include/eulercromer.h
  include/midpoint.h
  include/huen.h
  include/implicitodesolver.h
  include/ieuler.h
  include/ieulercromer.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

add_executable(IOdeTest examples/implicit_solver_testing.cpp)
target_link_libraries(IOdeTest PUBLIC ${PROJECT_NAME})
