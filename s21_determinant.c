#include "s21_matrix.h"
#include "s21_matrix_helpers.h"

int s21_determinant(s21_matrix* A, double* result) {
  int status = 1;

  if (A == NULL || result == NULL) {
    status = 1;
  } else if (!s21_is_matrix_valid(A)) {
    status = 1;
  } else if (!s21_is_square_matrix(A)) {
    status = 2;
  } else {
    status = s21_determinant_core(A, result);
  }

  return status;
}
