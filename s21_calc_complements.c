#include "s21_matrix.h"
#include "s21_matrix_helpers.h"

static int s21_calc_algebraic_complement(const s21_matrix* A, int row, int col,
                                         double* value) {
  int status = 0;
  s21_matrix minor = {0};
  double minor_det = 0.0;
  double sign = ((row + col) % 2 == 0) ? 1.0 : -1.0;

  status = s21_create_minor(A, row, col, &minor);
  if (status == 0) {
    status = s21_determinant_core(&minor, &minor_det);
  }
  if (status == 0) {
    *value = sign * minor_det;
  }
  s21_remove_matrix(&minor);

  return status;
}

static int s21_fill_complements(const s21_matrix* A, s21_matrix* result) {
  int status = 0;

  for (int i = 0; i < A->rows && status == 0; i++) {
    for (int j = 0; j < A->columns && status == 0; j++) {
      status = s21_calc_algebraic_complement(A, i, j, &result->matrix[i][j]);
    }
  }

  return status;
}

int s21_calc_complements(s21_matrix* A, s21_matrix* result) {
  int status = 0;

  if (A == NULL || result == NULL) {
    status = 1;
  } else if (!s21_is_matrix_valid(A)) {
    status = 1;
  } else if (!s21_is_square_matrix(A)) {
    status = 2;
  } else {
    status = s21_create_result_matrix(result, A->rows, A->columns);
    if (status == 0) {
      status = s21_fill_complements(A, result);
    }
  }

  return status;
}
