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

START_TEST(mult_number_null_pointers) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_mult_number(NULL, 2.0, &matrix), 1);
  ck_assert_int_eq(s21_mult_number(&matrix, 2.0, NULL), 1);
}
END_TEST

START_TEST(mult_number_invalid_matrices) {
  s21_matrix empty = {0};
  s21_matrix valid = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &valid), 0);
  ck_assert_int_eq(s21_mult_number(&empty, 2.0, &result), 1);
  ck_assert_int_eq(s21_mult_number(&valid, 2.0, &result), 0);
  s21_remove_matrix(&valid);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_readme_example) {
  s21_matrix a = {0};
  s21_matrix result = {0};
  s21_matrix expected = {0};
  double a_vals[] = {1, 2, 3, 0, 4, 2, 2, 3, 4};
  double exp_vals[] = {2, 4, 6, 0, 8, 4, 4, 6, 8};

  ck_assert_int_eq(s21_create_matrix(3, 3, &a), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &expected), 0);
  fill_matrix(&a, a_vals);
  fill_matrix(&expected, exp_vals);
  ck_assert_int_eq(s21_mult_number(&a, 2.0, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_number_negative_and_zero) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  a.matrix[0][0] = -2.5;
  ck_assert_int_eq(s21_mult_number(&a, 0.0, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-6);
  ck_assert_int_eq(s21_mult_number(&a, -1.0, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 2.5, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

Suite* mult_number_suite(void) {
  Suite* suite = suite_create("mult_number");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, mult_number_null_pointers);
  tcase_add_test(tc_core, mult_number_invalid_matrices);
  tcase_add_test(tc_core, mult_number_readme_example);
  tcase_add_test(tc_core, mult_number_negative_and_zero);
  suite_add_tcase(suite, tc_core);

  return suite;
}
