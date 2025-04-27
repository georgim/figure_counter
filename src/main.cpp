// src/main.cpp
#include "figure_counter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cerrno>

static std::string getInputFilePath(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <input_file_path>");
    }

    return argv[1];
}

static matrix_t fillMatrix(const std::string& inputFileName) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error(
            "Error: Could not open file " + inputFileName + ". Reason: " + std::strerror(errno)
        );
    }

    int rows, cols;
    std::string line;

    // Read the dimensions from the first line
    if (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        if (!(iss >> rows >> cols)) {
            throw std::runtime_error("Error: Failed to read matrix dimensions");
        }
    } else {
        throw std::runtime_error("Error: Input file is empty");
    }

    if (rows <= 0 || cols <= 0) {
        throw std::runtime_error("Error: The matrix should have positive numbers dimensions " +
            std::to_string(rows) + "x" + std::to_string(cols));
    }

    matrix_t matrix(rows, matrix_row_t(cols));

    for (auto i = 0; i < rows; i++) {
        if (!std::getline(inputFile, line)) {
            throw std::runtime_error("Error: Not enough rows in the matrix. Expected " +
                std::to_string(rows) + ", got " + std::to_string(i));
        }

        if (line.length() != static_cast<size_t>(cols)) {
            throw std::runtime_error("Error: Row " + std::to_string(i) + " has incorrect length. Expected " +
                std::to_string(cols) + ", got " + std::to_string(line.length()));
        }

        for (auto j = 0; j < cols; j++) {
            if (line[j] == BLANK_CHAR) {
                matrix[i][j] = BLANK;
            } else if (line[j] == COLORED_CHAR) {
                matrix[i][j] = COLORED;
            } else {
                throw std::runtime_error(
                    "Error: Invalid character in matrix at row " + std::to_string(i) +
                    ", column " + std::to_string(j) + ". Expected '0' or '1', got '" + line[j] + "'");
            }
        }
    }

    // inputFile will be closed automatically when it goes out of scope
    return matrix;
}

int main(int argc, char* argv[]) {
    try {
        auto inputFileName = getInputFilePath(argc, argv);
        auto matrix = fillMatrix(inputFileName);

        long figures = countFigures(matrix);
        std::cout << figures << " figure" << (figures == 1 ? "" : "s") << std::endl;

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}
