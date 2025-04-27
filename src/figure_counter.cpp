// src/figure_counter.cpp
#include "figure_counter.h"
#include <queue>
#include <stack>
#include <utility>
#include <limits>
#include <iostream>


// Define the four directions: up, right, down, left
constexpr std::pair<int, int> directions[] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

static inline void visitCell(
    std::queue<std::pair<std::size_t, std::size_t>>& q,
    matrix_t& matrix,
    std::size_t row,
    std::size_t col
) {
    matrix[row][col] = COLORED_VISITED;
    q.push({row, col});
}

/**
 * Function to calculate the new cell index based on the direction and the current cell index
 * Returns a pair: the new cell index and a boolean indicating if the index is valid
 * If the index is invalid, it returns 0 and false
 * This function is used to handle the edge cases where the index goes out of bounds in the matrix
 * and to take into account the sign of the types
*/
static inline std::pair<std::size_t, bool> calculateCellIndex(
    std::size_t cellIndex,
    int direction,
    std::size_t matrixDimension
) {
    if (direction == -1 && cellIndex == 0) {
        return {0, false};
    }
    if (direction == 1 && cellIndex == std::numeric_limits<std::size_t>::max()) {
        return {0, false};
    }
    auto newCellIndex = cellIndex + direction;
    if (newCellIndex >= matrixDimension) {
        return {0, false};
    }
    return {newCellIndex, true};
}

// Function to perform BFS and mark all connected cells as visited
static void markFigureCells(
    matrix_t& matrix,
    std::size_t startRow,
    std::size_t startCol,
    std::size_t matrixRows,
    std::size_t matrixCols
) {
    std::queue<std::pair<std::size_t, std::size_t>> q;
    visitCell(q, matrix, startRow, startCol);

    while (!q.empty()) {
        auto row = q.front().first;
        auto col = q.front().second;
        q.pop();

        // Check all four adjacent cells
        for (auto & direction : directions) {
            auto newRow = calculateCellIndex(row, direction.first, matrixRows);
            auto newCol = calculateCellIndex(col, direction.second, matrixCols);

            // Check if the new position is valid, is colored, and not yet visited
            if (newRow.second && newCol.second &&
                matrix[newRow.first][newCol.first] == COLORED) {
                visitCell(q, matrix, newRow.first, newCol.first);
            }
        }
    }
}

long countFigures(matrix_t& matrix) {
    const auto matrixRows = matrix.size();
    const auto matrixCols = matrix[0].size();
    long figureCount = 0;

    for (auto i = 0; i < matrixRows; i++) {
        for (auto j = 0; j < matrixCols; j++) {
            if (matrix[i][j] == COLORED) {
                figureCount++;
                markFigureCells(matrix, i, j, matrixRows, matrixCols);
            }
        }
    }

    return figureCount;
}