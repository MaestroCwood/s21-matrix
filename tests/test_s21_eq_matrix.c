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

START_TEST(eq_matrix_null_pointers) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_eq_matrix(NULL, &matrix), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&matrix, NULL), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);
}
END_TEST

START_TEST(eq_matrix_invalid_matrices) {
  s21_matrix empty = {0};
  s21_matrix valid = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &valid), 0);
  ck_assert_int_eq(s21_eq_matrix(&empty, &valid), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&valid, &empty), FAILURE);
  s21_remove_matrix(&valid);
}
END_TEST

START_TEST(eq_matrix_different_sizes) {
  s21_matrix a = {0};
  s21_matrix b = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &b), 0);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_equal_values) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  double values[] = {1.0, 2.0, -3.5, 0.123456};

  ck_assert_int_eq(s21_create_matrix(2, 2, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &b), 0);
  fill_matrix(&a, values);
  fill_matrix(&b, values);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_different_values) {
  s21_matrix a = {0};
  s21_matrix b = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &b), 0);
  a.matrix[0][0] = 1.0;
  b.matrix[0][0] = 2.0;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_sixth_decimal_precision) {
  s21_matrix a = {0};
  s21_matrix b = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &b), 0);
  a.matrix[0][0] = 1.123456;
  b.matrix[0][0] = 1.1234564;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  b.matrix[0][0] = 1.123458;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), FAILURE);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_rectangular) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  double values[] = {1.5, -2.5, 3.5, 4.5, -5.5, 6.5};

  ck_assert_int_eq(s21_create_matrix(2, 3, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &b), 0);
  fill_matrix(&a, values);
  fill_matrix(&b, values);
  ck_assert_int_eq(s21_eq_matrix(&a, &b), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

Suite* eq_matrix_suite(void) {
  Suite* suite = suite_create("eq_matrix");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, eq_matrix_null_pointers);
  tcase_add_test(tc_core, eq_matrix_invalid_matrices);
  tcase_add_test(tc_core, eq_matrix_different_sizes);
  tcase_add_test(tc_core, eq_matrix_equal_values);
  tcase_add_test(tc_core, eq_matrix_different_values);
  tcase_add_test(tc_core, eq_matrix_sixth_decimal_precision);
  tcase_add_test(tc_core, eq_matrix_rectangular);
  suite_add_tcase(suite, tc_core);

  return suite;
}
