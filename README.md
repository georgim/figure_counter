# Figure Counter

A C++ project to count the number of connected "figures" (groups of adjacent colored cells) in a matrix. The project includes a main executable, a test case generator and automated tests.

The program keep the entire matrix in memory and uses BFS algorithm with a queue to traverse its colored cells. BFS is used instead of standard recursive DFS implementation in order to avoid stack overflow error for large figures. The value of the visited matrix cells are modified in place.

---

## Requirements

- C++17 or newer compiler
- CMake 3.10 or newer

---

## Build Instructions

1. **Clone the repository and enter the project directory:**
    ```sh
    git clone https://github.com/georgim/figure_counter.git
    cd figure_counter
    ```

2. **Create a build directory and configure the project:**
    ```sh
    cmake -B build
    ```

3. **Build all targets:**
    ```sh
    cmake --build build --config Release
    ```
    This will build:
    - `figure_counter` (main program)
    - `test_generator` (test case generator)

---

## Generating And Running Test Cases

1. **Generate the large test matrices used by the integration tests:**

    ```sh
    cmake --build build --target generate_tests
    ```

    This will create a `test_cases/` directory in your build folder with all required test files.


2. **Run all tests (unit and integration) using CTest**

    ```sh
    ctest build/
    ```

    This will:
    - Run the integration tests using `figure_counter` on the generated test cases

> **Note:** Some test cases (like `chess_100000x100000.txt`) are very large and may take significant disk space and time to generate. These test cases also can take minutes to run and require up to 10G RAM


---

## Usage

To run the main program manually:

```sh
./figure_counter <input_file>
```

Where `<input_file>` is a text file with the following format:
```
<rows> <cols>
<row1>
<row2>
...
<rowN>
```
Each row consists of `0` (blank) and `1` (colored) characters.

---

## Example

Input file:
```
3 3
010
111
010
```

Command:
```sh
./figure_counter input.txt
```

Output:
```
1 figure
```

---