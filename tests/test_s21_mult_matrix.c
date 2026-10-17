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

START_TEST(mult_matrix_null_pointers) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_mult_matrix(NULL, &matrix, &matrix), 1);
  ck_assert_int_eq(s21_mult_matrix(&matrix, NULL, &matrix), 1);
  ck_assert_int_eq(s21_mult_matrix(&matrix, &matrix, NULL), 1);
}
END_TEST

START_TEST(mult_matrix_invalid_matrices) {
  s21_matrix empty = {0};
  s21_matrix valid = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &valid), 0);
  ck_assert_int_eq(s21_mult_matrix(&empty, &valid, &result), 1);
  ck_assert_int_eq(s21_mult_matrix(&valid, &empty, &result), 1);
  s21_remove_matrix(&valid);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_incompatible_sizes) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 3, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 2, &b), 0);
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &result), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(mult_matrix_readme_example) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};
  s21_matrix expected = {0};
  double a_vals[] = {1, 4, 2, 5, 3, 6};
  double b_vals[] = {1, -1, 1, 2, 3, 4};
  double exp_vals[] = {9, 11, 17, 12, 13, 22, 15, 15, 27};

  ck_assert_int_eq(s21_create_matrix(3, 2, &a), 0);
  ck_assert_int_eq(s21_create_matrix(2, 3, &b), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &expected), 0);
  fill_matrix(&a, a_vals);
  fill_matrix(&b, b_vals);
  fill_matrix(&expected, exp_vals);
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(mult_matrix_1x1) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  ck_assert_int_eq(s21_create_matrix(1, 1, &b), 0);
  a.matrix[0][0] = -2.0;
  b.matrix[0][0] = 3.5;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], -7.0, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_rectangular) {
  s21_matrix a = {0};
  s21_matrix b = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 3, &a), 0);
  ck_assert_int_eq(s21_create_matrix(3, 2, &b), 0);
  a.matrix[0][0] = 1.0;
  a.matrix[0][1] = 2.0;
  a.matrix[0][2] = 3.0;
  b.matrix[0][0] = 1.0;
  b.matrix[1][0] = 2.0;
  b.matrix[2][0] = 3.0;
  ck_assert_int_eq(s21_mult_matrix(&a, &b, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 14.0, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

Suite* mult_matrix_suite(void) {
  Suite* suite = suite_create("mult_matrix");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, mult_matrix_null_pointers);
  tcase_add_test(tc_core, mult_matrix_invalid_matrices);
  tcase_add_test(tc_core, mult_matrix_incompatible_sizes);
  tcase_add_test(tc_core, mult_matrix_readme_example);
  tcase_add_test(tc_core, mult_matrix_1x1);
  tcase_add_test(tc_core, mult_matrix_rectangular);
  suite_add_tcase(suite, tc_core);

  return suite;
}
