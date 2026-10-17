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

START_TEST(sub_matrix_null_pointers) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_sub_matrix(NULL, &matrix, &matrix), 1);
  ck_assert_int_eq(s21_sub_matrix(&matrix, NULL, &matrix), 1);
  ck_assert_int_eq(s21_sub_matrix(&matrix, &matrix, NULL), 1);
}
END_TEST

START_TEST(sub_matrix_invalid_matrices) {
  s21_matrix empty = {0};
  s21_matrix valid = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &valid), 0);
  ck_assert_int_eq(s21_sub_matrix(&empty, &valid, &result), 1);
  ck_assert_int_eq(s21_sub_matrix(&valid, &empty, &result), 1);
  s21_remove_matrix(&valid);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_different_sizes) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(3, 2, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &b), 0);
  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sub_matrix_basic) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};
  double a_vals[] = {5.5, 3.0, 1.0, 2.0};
  double b_vals[] = {1.5, 1.0, 0.5, 2.0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &b), 0);
  fill_matrix(&a, a_vals);
  fill_matrix(&b, b_vals);
  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_1x1) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &b), 0);
  a.matrix[0][0] = -1.25;
  b.matrix[0][0] = -2.75;
  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.5, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_rectangular) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 3, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &b), 0);
  a.matrix[0][0] = 10.0;
  a.matrix[1][2] = -4.5;
  b.matrix[0][0] = 3.5;
  b.matrix[1][2] = -1.5;
  ck_assert_int_eq(s21_sub_matrix(&a, &b, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 6.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][2], -3.0, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

Suite* sub_matrix_suite(void) {
  Suite* suite = suite_create("sub_matrix");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, sub_matrix_null_pointers);
  tcase_add_test(tc_core, sub_matrix_invalid_matrices);
  tcase_add_test(tc_core, sub_matrix_different_sizes);
  tcase_add_test(tc_core, sub_matrix_basic);
  tcase_add_test(tc_core, sub_matrix_1x1);
  tcase_add_test(tc_core, sub_matrix_rectangular);
  suite_add_tcase(suite, tc_core);

  return suite;
}
