#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>
#include "figure_counter.h"

static void generateFilledMatrix(
    const std::string& filename,
    std::size_t rows,
    std::size_t cols,
    const std::function<char(const std::size_t, const std::size_t)>& fillFunc
) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file << rows << " " << cols << std::endl;
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            file << fillFunc(i, j);
        }
        file << std::endl;
    }
}

int main() {
    // Create test directory if it doesn't exist
    std::filesystem::create_directory("test_cases");

    // Test 1: Blank matrix 1000x1000
    generateFilledMatrix(
        "test_cases/blank_1000x1000.txt",
        1000,
        1000,
        [](std::size_t, std::size_t) { return BLANK_CHAR; }
    );
    std::cout << "Generated blank matrix 1000x1000 in test_cases/blank_1000x1000.txt" << std::endl;

    // Test 2: 1x1000000 with chess colored cells
    // For large matrices, use a lower probability to avoid excessive memory usage
    generateFilledMatrix(
        "test_cases/chess_1x1000000.txt",
        1,
        1000000,
        [](std::size_t i, std::size_t j) { return ((i + j) % 2) ? COLORED_CHAR : BLANK_CHAR; }
    );
    std::cout << "Generated single line matrix in test_cases/chess_1x1000000.txt" << std::endl;

    // Test 3: 1000000x1 with chess colored cells
    generateFilledMatrix(
        "test_cases/chess_1000000x1.txt",
        1000000,
        1,
        [](std::size_t i, std::size_t j) { return ((i + j) % 2) ? COLORED_CHAR : BLANK_CHAR; }
    );
    std::cout << "Generated single column matrix in test_cases/chess_1000000x1.txt" << std::endl;

    // Test 4: 1000x1000 fully colored matrix
    generateFilledMatrix(
        "test_cases/full_1000x1000.txt",
        1000,
        1000,
        [](std::size_t, std::size_t) { return COLORED_CHAR; }
    );
    std::cout << "Generated full matrix 1000x1000 in test_cases/full_1000x1000.txt" << std::endl;

     // Test 5: 1000x200 with colored boundaries
     generateFilledMatrix(
        "test_cases/boundary_1000x200.txt",
        1000,
        200,
        [](std::size_t i, std::size_t j) {
            return (i == 0 || i == 999 || j == 0 || j == 199) ? COLORED_CHAR : BLANK_CHAR;
        }
    );
    std::cout << "Generated matrix with boundary 1000x200 in test_cases/boundary_1000x200.txt" << std::endl;

    // Test 6: Chess pattern 10000x10000
    // Note: This creates a large file of ~100MB
    generateFilledMatrix(
        "test_cases/chess_10000x10000.txt",
        10000,
        10000,
        [](std::size_t i, std::size_t j) { return ((i + j) % 2) ? COLORED_CHAR : BLANK_CHAR; }
    );
    std::cout << "Generated chess matrix 10000x10000 in test_cases/chess_10000x10000.txt" << std::endl;

    // Test 7: Chess pattern 100000x100000
    // Note: This creates a very large file of ~10GB
    generateFilledMatrix(
        "test_cases/chess_100000x100000.txt",
        100000,
        100000,
        [](std::size_t i, std::size_t j) { return ((i + j) % 2) ? COLORED_CHAR : BLANK_CHAR; }
    );
    std::cout << "Generated chess matrix 100000x100000 in test_cases/chess_100000x100000.txt" << std::endl;

    std::cout << "All test files generated!" << std::endl;
    return 0;
}
