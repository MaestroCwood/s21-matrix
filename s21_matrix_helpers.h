#ifndef S21_MATRIX_HELPERS_H
#define S21_MATRIX_HELPERS_H

#include <math.h>

#include "s21_matrix.h"

#define S21_EPSILON 1e-6

int s21_is_matrix_valid(const s21_matrix* matrix);
int s21_is_same_size(const s21_matrix* A, const s21_matrix* B);
int s21_is_square_matrix(const s21_matrix* matrix);
int s21_is_double_equal(double a, double b);
int s21_allocate_matrix_rows(s21_matrix* matrix, int rows, int columns);
void s21_free_partial_matrix(s21_matrix* matrix, int allocated_rows);
int s21_create_result_matrix(s21_matrix* result, int rows, int columns);
int s21_create_minor(const s21_matrix* A, int skip_row, int skip_col,
                     s21_matrix* minor);
int s21_determinant_core(const s21_matrix* A, double* result);

#endif  // S21_MATRIX_HELPERS_H
