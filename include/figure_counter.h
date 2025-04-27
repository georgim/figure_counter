// include/figure_counter.h
#ifndef FIGURE_COUNTER_H
#define FIGURE_COUNTER_H

#include <vector>
#include <cstdint>

constexpr int8_t BLANK = 0;
constexpr char BLANK_CHAR = '0' + BLANK;
constexpr int8_t COLORED = 1;
constexpr char COLORED_CHAR = '0' + COLORED;

constexpr int8_t COLORED_VISITED = -1;

using matrix_row_t = std::vector<int8_t>;
using matrix_t = std::vector<std::vector<int8_t>>;
long countFigures(matrix_t& matrix);

#endif // FIGURE_COUNTER_H
