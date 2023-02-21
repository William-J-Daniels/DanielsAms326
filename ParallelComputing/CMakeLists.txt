cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(ParallelComputing VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
  include/threadpool.h
  src/threadpool.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/threadpool.h
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEARER "${public_headers}")

add_executable(thread_pool_example examples/thread_pool_example.cpp)
target_link_libraries(thread_pool_example PUBLIC ${PROJECT_NAME})
