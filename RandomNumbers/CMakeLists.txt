cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(random_numbers VERSION 0.1.0)

add_library(${PROJECT_NAME} SHARED
  include/lcg.h
  src/lcg.cpp
  include/uniformgenerator.h
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/lcg.h
  include/uniformgenerator.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
  "${public_headers}"
)

add_executable(lcg_example examples/lcg_example.cpp)
target_link_libraries(lcg_example PUBLIC ${PROJECT_NAME})

add_executable(uniformgenerator_example examples/uniformgenerator_example.cpp)
target_link_libraries(uniformgenerator_example PUBLIC ${PROJECT_NAME})
