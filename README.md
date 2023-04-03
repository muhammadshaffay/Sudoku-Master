# Sudoku-Master
Sudoku Master: A Multi-threaded Validator and Solver

Sudoku Master is a multi-threaded validator and solver program designed to solve a 9x9 Sudoku matrix using thread-based concurrency and mutex synchronization. This project consists of two main parts: the validator and the solver. The validator checks whether a given 9x9 matrix qualifies as a Sudoku puzzle or not. The validator uses mutex synchronization to prevent race conditions that may occur while accessing shared data structures. It also uses multiple threads to speed up the process of validating the puzzle.

The solver, on the other hand, takes a wrongly filled puzzle as input and uses a multi-threaded approach to correct it. The solver uses a backtracking algorithm to solve the Sudoku puzzle, and mutexes are used to ensure that the shared data structures are not corrupted during concurrent access.

Sudoku Master is a project that combines the principles of thread-based concurrency and mutex synchronization to solve and validate Sudoku puzzles. This project is ideal for students and enthusiasts who want to learn about multi-threading and mutex synchronization in practical applications. It can be used as a basis for building more complex applications that require high-performance computing capabilities.
