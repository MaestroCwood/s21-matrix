#include "s21_matrix.h"
#include "s21_matrix_helpers.h"

static int s21_compare_matrices(const s21_matrix* A, const s21_matrix* B) {
  int status = SUCCESS;

  for (int i = 0; i < A->rows && status == SUCCESS; i++) {
    for (int j = 0; j < A->columns && status == SUCCESS; j++) {
      if (!s21_is_double_equal(A->matrix[i][j], B->matrix[i][j])) {
        status = FAILURE;
      }
    }
  }

  return status;
}

int s21_eq_matrix(s21_matrix* A, s21_matrix* B) {
  int status = FAILURE;

  if (s21_is_matrix_valid(A) && s21_is_matrix_valid(B)) {
    if (s21_is_same_size(A, B)) {
      status = s21_compare_matrices(A, B);
    }
  }

  return status;
}
