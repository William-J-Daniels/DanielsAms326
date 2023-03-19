cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Integration VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
  include/integrator.h
  src/integrator.cpp
  include/midpoint.h
  src/midpoint.cpp
  include/trapezoid.h
  src/trapezoid.cpp
  include/simpson.h
  src/simpson.cpp
  include/boole.h
  src/boole.cpp
  include/montecarlo.h
  src/montecarlo.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} PUBLIC random_numbers)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
  include/integrator.h
  include/midpoint.h
  include/trapezoid.h
  include/simpson.h
  include/boole.h
  include/montecarlo.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEARER "${public_headers}")

add_executable(MidpointTest examples/MidpointExample.cpp)
target_link_libraries(MidpointTest PUBLIC ${PROJECT_NAME})

add_executable(TrapezoidTest examples/TrapezoidExample.cpp)
target_link_libraries(TrapezoidTest PUBLIC ${PROJECT_NAME})

add_executable(SimpsonsTest examples/SimpsonsExample.cpp)
target_link_libraries(SimpsonsTest PUBLIC ${PROJECT_NAME})

add_executable(BooleTest examples/BooleExample.cpp)
target_link_libraries(BooleTest PUBLIC ${PROJECT_NAME})

add_executable(MonteCarloTest examples/MonteCarloExample.cpp)
target_link_libraries(MonteCarloTest PUBLIC ${PROJECT_NAME})
