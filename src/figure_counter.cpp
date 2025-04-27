// src/figure_counter.cpp
#include "figure_counter.h"
#include <queue>
#include <stack>
#include <utility>

// Define the four directions: up, right, down, left
constexpr std::pair<int, int> directions[] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

static inline void visitCell(
    std::queue<std::pair<int, int>>& q,
    matrix_t& matrix,
    const int row,
    const int col
) {
    matrix[row][col] = COLORED_VISITED;
    q.push({row, col});
}

// Function to perform BFS and mark all connected cells as visited
static void markFigureCells(
    matrix_t& matrix,
    const int startRow,
    const int startCol,
    const std::size_t matrixRows,
    const std::size_t matrixCols
) {
    std::queue<std::pair<int, int>> q;
    visitCell(q, matrix, startRow, startCol);

    while (!q.empty()) {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        // Check all four adjacent cells
        for (auto & direction : directions) {
            int newRow = row + direction.first;
            int newCol = col + direction.second;

            // Check if the new position is valid, is colored, and not yet visited
            if (newRow >= 0 && newRow < matrixRows &&
                newCol >= 0 && newCol < matrixCols &&
                matrix[newRow][newCol] == COLORED) {
                visitCell(q, matrix, newRow, newCol);
            }
        }
    }
}

int countFigures(matrix_t& matrix) {
    const std::size_t matrixRows = matrix.size();
    const std::size_t matrixCols = matrix[0].size();
    int figureCount = 0;

    for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixCols; j++) {
            if (matrix[i][j] == COLORED) {
                figureCount++;
                markFigureCells(matrix, i, j, matrixRows, matrixCols);
            }
        }
    }

    return figureCount;
}