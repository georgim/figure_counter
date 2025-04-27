cmake_minimum_required(VERSION 3.10)
project(FigureCounter VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
    src/figure_counter.cpp
)

add_executable(figure_counter ${SOURCES})
target_include_directories(figure_counter PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_executable(test_generator test/test_generator.cpp)
target_include_directories(test_generator PUBLIC "${PROJECT_SOURCE_DIR}/include")

enable_testing()

# Add custom target to generate test files
add_custom_target(generate_tests
    COMMAND test_generator
    DEPENDS test_generator
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating test cases..."
)

function(do_test name target arg result)
  add_test(NAME ${name} COMMAND ${target} ${arg})
  set_tests_properties(${name}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_test(SmallTest figure_counter "${PROJECT_SOURCE_DIR}/test/small_test.txt" "3 figures")

# Add performance tests (these will be available after running the test generator)
do_test(BlankMatrixTest figure_counter ${CMAKE_BINARY_DIR}/test_cases/blank_1000x1000.txt "0 figures")
do_test(HorizontalTest figure_counter ${CMAKE_BINARY_DIR}/test_cases/chess_1x1000000.txt "500000 figures")
do_test(VerticalTest figure_counter ${CMAKE_BINARY_DIR}/test_cases/chess_1000000x1.txt "500000 figures")
do_test(FullMatrixTest figure_counter ${CMAKE_BINARY_DIR}/test_cases/full_1000x1000.txt "1 figure")
do_test(BoundaryMatrixTest figure_counter ${CMAKE_BINARY_DIR}/test_cases/boundary_1000x200.txt "1 figure")
do_test(ChessMatrixTest figure_counter ${CMAKE_BINARY_DIR}/test_cases/chess_10000x10000.txt "50000000 figures")
do_test(ExtremeChessMatrixTest figure_counter ${CMAKE_BINARY_DIR}/test_cases/chess_100000x100000.txt "5000000000 figures")
