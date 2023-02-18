cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(root_finding VERSION 0.1.0)

add_library(${PROJECT_NAME} SHARED
  include/rootfinder.h
  src/rootfinder.cpp
  include/bisection.h
  src/bisection.cpp
  include/newtonraphson.h
  src/newtonraphson.cpp
  include/secant.h
  src/secant.cpp
  include/fixedpoint.h
  src/fixedpoint.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC Differentiation)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/rootfinder.h
  include/bisection.h
  include/newtonraphson.h
  include/secant.h
  include/fixedpoint.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
  "${public_headers}"
)

add_executable(bisection_example examples/bisection_example.cpp)
target_link_libraries(bisection_example PUBLIC ${PROJECT_NAME})

add_executable(newton_example examples/newton_example.cpp)
target_link_libraries(newton_example PUBLIC ${PROJECT_NAME})

add_executable(secant_example examples/secant_example.cpp)
target_link_libraries(secant_example PUBLIC ${PROJECT_NAME})

add_executable(fixed_point_example examples/fixed_point_example.cpp)
target_link_libraries(fixed_point_example PUBLIC ${PROJECT_NAME})
