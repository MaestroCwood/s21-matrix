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

START_TEST(calc_complements_null_pointers) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_calc_complements(NULL, &matrix), 1);
  ck_assert_int_eq(s21_calc_complements(&matrix, NULL), 1);
}
END_TEST

START_TEST(calc_complements_invalid_matrix) {
  s21_matrix empty = {0};
  s21_matrix valid = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(3, 3, &valid), 0);
  ck_assert_int_eq(s21_calc_complements(&empty, &result), 1);
  s21_remove_matrix(&valid);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_non_square) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 3, &a), 0);
  ck_assert_int_eq(s21_calc_complements(&a, &result), 2);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(calc_complements_readme_example) {
  s21_matrix a = {0};
  s21_matrix result = {0};
  s21_matrix expected = {0};
  double a_vals[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double exp_vals[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};

  ck_assert_int_eq(s21_create_matrix(3, 3, &a), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &expected), 0);
  fill_matrix(&a, a_vals);
  fill_matrix(&expected, exp_vals);
  ck_assert_int_eq(s21_calc_complements(&a, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(calc_complements_1x1) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  a.matrix[0][0] = 5.0;
  ck_assert_int_eq(s21_calc_complements(&a, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2x2) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &a), 0);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[1][0] = 3.0;
  a.matrix[1][1] = 4.0;
  ck_assert_int_eq(s21_calc_complements(&a, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

Suite* calc_complements_suite(void) {
  Suite* suite = suite_create("calc_complements");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, calc_complements_null_pointers);
  tcase_add_test(tc_core, calc_complements_invalid_matrix);
  tcase_add_test(tc_core, calc_complements_non_square);
  tcase_add_test(tc_core, calc_complements_readme_example);
  tcase_add_test(tc_core, calc_complements_1x1);
  tcase_add_test(tc_core, calc_complements_2x2);
  suite_add_tcase(suite, tc_core);

  return suite;
}
