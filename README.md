# s21_matrix

A C library for matrix operations, written while studying at School 21 (Backend).

The public API is in `s21_matrix.h`. Helper functions live in `s21_matrix_helpers.c`.

## Operations

- create and remove a matrix
- compare two matrices
- add, subtract, multiply by a number, multiply two matrices
- transpose
- determinant
- matrix of algebraic complements
- inverse matrix

## Build and test

The tests use the [Check](https://libcheck.github.io/check/) library. On MinGW the Makefile links only `-lcheck`. On Linux it also links `-lsubunit`.

```bash
make
make test
```

`make` builds `s21_matrix.a` and `test.out`. `make test` runs the existing tests in `tests/`. `make gcov_report` needs `lcov`.

## Limitations

The code follows the School 21 matrix assignment: a matrix is a struct with `rows`, `columns`, and a `double **matrix`. Error codes are returned as `int`. There is no extra command-line program around the library.
