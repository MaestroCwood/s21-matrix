#include "s21_matrix.h"
#include "s21_matrix_helpers.h"

int s21_create_matrix(int rows, int columns, s21_matrix* result) {
  int status = 1;

  if (result != NULL && rows > 0 && columns > 0) {
    status = s21_allocate_matrix_rows(result, rows, columns);
  }

  return status;
}
