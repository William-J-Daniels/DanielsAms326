cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Differentiation VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
  include/differentiator.h
  src/differentiator.cpp
  include/firstderivative.h
  src/firstderivative.cpp
  include/secondderivative.h
  src/secondderivative.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/differentiator.h
  include/firstderivative.h
  include/secondderivative.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

add_executable(first_order_example examples/first_order_example.cpp)
target_link_libraries(first_order_example PUBLIC ${PROJECT_NAME})
