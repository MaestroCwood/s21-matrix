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

START_TEST(transpose_null_pointers) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_transpose(NULL, &matrix), 1);
  ck_assert_int_eq(s21_transpose(&matrix, NULL), 1);
}
END_TEST

START_TEST(transpose_invalid_matrices) {
  s21_matrix empty = {0};
  s21_matrix valid = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 3, &valid), 0);
  ck_assert_int_eq(s21_transpose(&empty, &result), 1);
  ck_assert_int_eq(s21_transpose(&valid, &result), 0);
  s21_remove_matrix(&valid);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_readme_example) {
  s21_matrix a = {0};
  s21_matrix result = {0};
  s21_matrix expected = {0};
  double a_vals[] = {1, 4, 2, 5, 3, 6};
  double exp_vals[] = {1, 2, 3, 4, 5, 6};

  ck_assert_int_eq(s21_create_matrix(3, 2, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &expected), 0);
  fill_matrix(&a, a_vals);
  fill_matrix(&expected, exp_vals);
  ck_assert_int_eq(s21_transpose(&a, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(transpose_square_2x2) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &a), 0);
  a.matrix[0][0] = 1.5;
  a.matrix[0][1] = -2.5;
  a.matrix[1][0] = 3.5;
  a.matrix[1][1] = 4.5;
  ck_assert_int_eq(s21_transpose(&a, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.5, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_1x1) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  a.matrix[0][0] = -7.25;
  ck_assert_int_eq(s21_transpose(&a, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], -7.25, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

Suite* transpose_suite(void) {
  Suite* suite = suite_create("transpose");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, transpose_null_pointers);
  tcase_add_test(tc_core, transpose_invalid_matrices);
  tcase_add_test(tc_core, transpose_readme_example);
  tcase_add_test(tc_core, transpose_square_2x2);
  tcase_add_test(tc_core, transpose_1x1);
  suite_add_tcase(suite, tc_core);

  return suite;
}
