#include "s21_matrix.h"
#include "s21_matrix_helpers.h"

static int s21_build_inverse(const s21_matrix* A, s21_matrix* result,
                             double determinant) {
  int status = 0;
  s21_matrix complements = {0};
  s21_matrix transposed = {0};

  status = s21_create_matrix(A->rows, A->columns, &complements);
  if (status == 0) {
    status = s21_calc_complements((s21_matrix*)A, &complements);
  }
  if (status == 0) {
    status = s21_transpose(&complements, &transposed);
  }
  if (status == 0) {
    status = s21_mult_number(&transposed, 1.0 / determinant, result);
  }

  s21_remove_matrix(&complements);
  s21_remove_matrix(&transposed);

  return status;
}

int s21_inverse_matrix(s21_matrix* A, s21_matrix* result) {
  int status = 0;
  double det = 0.0;

  if (A == NULL || result == NULL) {
    status = 1;
  } else if (!s21_is_matrix_valid(A)) {
    status = 1;
  } else if (!s21_is_square_matrix(A)) {
    status = 2;
  } else {
    status = s21_determinant(A, &det);
    if (status == 0 && s21_is_double_equal(det, 0.0)) {
      status = 2;
    } else if (status == 0) {
      status = s21_build_inverse(A, result, det);
    }
  }

  return status;
}
