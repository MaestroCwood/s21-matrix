#include "s21_matrix.h"
#include "s21_matrix_helpers.h"

static int s21_multiply_matrices(const s21_matrix* A, const s21_matrix* B,
                                 s21_matrix* result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0.0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return 0;
}

int s21_mult_matrix(s21_matrix* A, s21_matrix* B, s21_matrix* result) {
  int status = 0;

  if (A == NULL || B == NULL || result == NULL) {
    status = 1;
  } else if (!s21_is_matrix_valid(A) || !s21_is_matrix_valid(B)) {
    status = 1;
  } else if (A->columns != B->rows) {
    status = 2;
  } else {
    status = s21_create_result_matrix(result, A->rows, B->columns);
    if (status == 0) {
      status = s21_multiply_matrices(A, B, result);
    }
  }

  return status;
}
