cmake_minimum_required(VERSION 3.10)
project(FigureCounter VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/figure_counter.cpp
)

add_executable(figure_counter ${SOURCES})

target_include_directories(figure_counter PUBLIC "${PROJECT_SOURCE_DIR}/include")