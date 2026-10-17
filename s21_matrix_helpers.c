#include "s21_matrix_helpers.h"

#include <stdlib.h>

#include "s21_matrix.h"

int s21_is_matrix_valid(const s21_matrix* matrix) {
  int status = 0;

  if (matrix != NULL && matrix->matrix != NULL && matrix->rows > 0 &&
      matrix->columns > 0) {
    status = 1;
  }

  return status;
}

int s21_is_same_size(const s21_matrix* A, const s21_matrix* B) {
  int status = 0;

  if (s21_is_matrix_valid(A) && s21_is_matrix_valid(B) && A->rows == B->rows &&
      A->columns == B->columns) {
    status = 1;
  }

  return status;
}

int s21_is_square_matrix(const s21_matrix* matrix) {
  int status = 0;

  if (s21_is_matrix_valid(matrix) && matrix->rows == matrix->columns) {
    status = 1;
  }

  return status;
}

int s21_is_double_equal(double a, double b) {
  return fabs(a - b) < S21_EPSILON;
}

void s21_free_partial_matrix(s21_matrix* matrix, int allocated_rows) {
  if (matrix != NULL && matrix->matrix != NULL) {
    for (int i = 0; i < allocated_rows; i++) {
      free(matrix->matrix[i]);
      matrix->matrix[i] = NULL;
    }
    free(matrix->matrix);
    matrix->matrix = NULL;
  }
  if (matrix != NULL) {
    matrix->rows = 0;
    matrix->columns = 0;
  }
}

int s21_create_result_matrix(s21_matrix* result, int rows, int columns) {
  s21_remove_matrix(result);
  return s21_create_matrix(rows, columns, result);
}

int s21_allocate_matrix_rows(s21_matrix* matrix, int rows, int columns) {
  int status = 0;
  int row = 0;

  matrix->rows = rows;
  matrix->columns = columns;
  matrix->matrix = (double**)calloc((size_t)rows, sizeof(double*));

  if (matrix->matrix == NULL) {
    status = 1;
  } else {
    for (; row < rows && status == 0; row++) {
      matrix->matrix[row] = (double*)calloc((size_t)columns, sizeof(double));
      if (matrix->matrix[row] == NULL) {
        s21_free_partial_matrix(matrix, row);
        status = 1;
      }
    }
  }

  return status;
}

static int s21_fill_minor(const s21_matrix* A, int skip_row, int skip_col,
                          s21_matrix* minor) {
  int mi = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i != skip_row) {
      int mj = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != skip_col) {
          minor->matrix[mi][mj] = A->matrix[i][j];
          mj++;
        }
      }
      mi++;
    }
  }
  return 0;
}

int s21_create_minor(const s21_matrix* A, int skip_row, int skip_col,
                     s21_matrix* minor) {
  int status = 1;
  int size = A->rows - 1;

  if (s21_is_square_matrix(A)) {
    if (size == 0) {
      minor->rows = 0;
      minor->columns = 0;
      minor->matrix = NULL;
      status = 0;
    } else {
      status = s21_create_matrix(size, size, minor);
      if (status == 0) {
        status = s21_fill_minor(A, skip_row, skip_col, minor);
      }
    }
  }

  return status;
}

static int s21_determinant_2x2(const s21_matrix* A, double* result) {
  *result =
      A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  return 0;
}

static int s21_determinant_by_row(const s21_matrix* A, double* result) {
  int status = 0;
  int n = A->rows;

  *result = 0.0;
  for (int j = 0; j < n && status == 0; j++) {
    s21_matrix minor = {0};
    double minor_det = 0.0;
    double sign = (j % 2 == 0) ? 1.0 : -1.0;

    status = s21_create_minor(A, 0, j, &minor);
    if (status == 0) {
      status = s21_determinant_core(&minor, &minor_det);
    }
    if (status == 0) {
      *result += sign * A->matrix[0][j] * minor_det;
    }
    s21_remove_matrix(&minor);
  }

  return status;
}

int s21_determinant_core(const s21_matrix* A, double* result) {
  int status = 0;

  if (A->rows == 0) {
    *result = 1.0;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    status = s21_determinant_2x2(A, result);
  } else {
    status = s21_determinant_by_row(A, result);
  }

  return status;
}
