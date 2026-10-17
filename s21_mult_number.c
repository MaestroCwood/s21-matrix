#include "s21_matrix.h"
#include "s21_matrix_helpers.h"

static int s21_scale_matrix(const s21_matrix* A, double number,
                            s21_matrix* result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return 0;
}

int s21_mult_number(s21_matrix* A, double number, s21_matrix* result) {
  int status = 0;

  if (A == NULL || result == NULL) {
    status = 1;
  } else if (!s21_is_matrix_valid(A)) {
    status = 1;
  } else {
    status = s21_create_result_matrix(result, A->rows, A->columns);
    if (status == 0) {
      status = s21_scale_matrix(A, number, result);
    }
  }

  return status;
}
