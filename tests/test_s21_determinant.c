#include <check.h>

#include "../s21_matrix.h"

static void fill_matrix(s21_matrix* matrix, const double* values) {
  int k = 0;
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = values[k++];
    }
  }
}

START_TEST(determinant_null_pointers) {
  s21_matrix matrix = {0};
  double value = 0.0;

  ck_assert_int_eq(s21_determinant(NULL, &value), 1);
  ck_assert_int_eq(s21_determinant(&matrix, NULL), 1);
}
END_TEST

START_TEST(determinant_invalid_matrix) {
  s21_matrix empty = {0};
  double value = 0.0;

  ck_assert_int_eq(s21_determinant(&empty, &value), 1);
}
END_TEST

START_TEST(determinant_non_square) {
  s21_matrix matrix = {0};
  double value = 0.0;

  ck_assert_int_eq(s21_create_matrix(2, 3, &matrix), 0);
  ck_assert_int_eq(s21_determinant(&matrix, &value), 2);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_1x1) {
  s21_matrix matrix = {0};
  double value = 0.0;

  ck_assert_int_eq(s21_create_matrix(1, 1, &matrix), 0);
  matrix.matrix[0][0] = -4.5;
  ck_assert_int_eq(s21_determinant(&matrix, &value), 0);
  ck_assert_double_eq_tol(value, -4.5, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_2x2) {
  s21_matrix matrix = {0};
  double value = 0.0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &matrix), 0);
  matrix.matrix[0][0] = 1.0;
  matrix.matrix[0][1] = 2.0;
  matrix.matrix[1][0] = 3.0;
  matrix.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_determinant(&matrix, &value), 0);
  ck_assert_double_eq_tol(value, -2.0, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_3x3_readme) {
  s21_matrix matrix = {0};
  double value = 1.0;
  double a_vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  ck_assert_int_eq(s21_create_matrix(3, 3, &matrix), 0);
  fill_matrix(&matrix, a_vals);
  ck_assert_int_eq(s21_determinant(&matrix, &value), 0);
  ck_assert_double_eq_tol(value, 0.0, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(determinant_3x3_non_zero) {
  s21_matrix matrix = {0};
  double value = 0.0;
  double a_vals[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};

  ck_assert_int_eq(s21_create_matrix(3, 3, &matrix), 0);
  fill_matrix(&matrix, a_vals);
  ck_assert_int_eq(s21_determinant(&matrix, &value), 0);
  ck_assert_double_eq_tol(value, -40.0, 1e-6);
  s21_remove_matrix(&matrix);
}
END_TEST

Suite* determinant_suite(void) {
  Suite* suite = suite_create("determinant");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, determinant_null_pointers);
  tcase_add_test(tc_core, determinant_invalid_matrix);
  tcase_add_test(tc_core, determinant_non_square);
  tcase_add_test(tc_core, determinant_1x1);
  tcase_add_test(tc_core, determinant_2x2);
  tcase_add_test(tc_core, determinant_3x3_readme);
  tcase_add_test(tc_core, determinant_3x3_non_zero);
  suite_add_tcase(suite, tc_core);

  return suite;
}
