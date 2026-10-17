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

START_TEST(inverse_matrix_null_pointers) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_inverse_matrix(NULL, &matrix), 1);
  ck_assert_int_eq(s21_inverse_matrix(&matrix, NULL), 1);
}
END_TEST

START_TEST(inverse_matrix_invalid_matrices) {
  s21_matrix empty = {0};
  s21_matrix valid = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(3, 3, &valid), 0);
  ck_assert_int_eq(s21_inverse_matrix(&empty, &result), 1);
  s21_remove_matrix(&valid);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_non_square) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 3, &a), 0);
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 2);
  s21_remove_matrix(&a);
}
END_TEST

START_TEST(inverse_matrix_zero_determinant) {
  s21_matrix a = {0};
  s21_matrix result = {0};
  double a_vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  ck_assert_int_eq(s21_create_matrix(3, 3, &a), 0);
  fill_matrix(&a, a_vals);
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_readme_example) {
  s21_matrix a = {0};
  s21_matrix result = {0};
  s21_matrix expected = {0};
  double a_vals[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double exp_vals[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};

  ck_assert_int_eq(s21_create_matrix(3, 3, &a), 0);
  ck_assert_int_eq(s21_create_matrix(3, 3, &expected), 0);
  fill_matrix(&a, a_vals);
  fill_matrix(&expected, exp_vals);
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_matrix_1x1) {
  s21_matrix a = {0};
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &a), 0);
  a.matrix[0][0] = 4.0;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.25, 1e-6);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_2x2) {
  s21_matrix a = {0};
  s21_matrix result = {0};
  s21_matrix identity = {0};
  s21_matrix check = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &a), 0);
  a.matrix[0][0] = 4.0;
  a.matrix[0][1] = 7.0;
  a.matrix[1][0] = 2.0;
  a.matrix[1][1] = 6.0;
  ck_assert_int_eq(s21_create_matrix(2, 2, &identity), 0);
  identity.matrix[0][0] = 1.0;
  identity.matrix[1][1] = 1.0;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);
  ck_assert_int_eq(s21_mult_matrix(&a, &result, &check), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &identity), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&identity);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(inverse_matrix_fractional) {
  s21_matrix a = {0};
  s21_matrix result = {0};
  s21_matrix identity = {0};
  s21_matrix check = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &a), 0);
  a.matrix[0][0] = 1.5;
  a.matrix[0][1] = -0.5;
  a.matrix[1][0] = 0.0;
  a.matrix[1][1] = 2.0;
  ck_assert_int_eq(s21_create_matrix(2, 2, &identity), 0);
  identity.matrix[0][0] = 1.0;
  identity.matrix[1][1] = 1.0;
  ck_assert_int_eq(s21_inverse_matrix(&a, &result), 0);
  ck_assert_int_eq(s21_mult_matrix(&a, &result, &check), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &identity), SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&identity);
  s21_remove_matrix(&check);
}
END_TEST

Suite* inverse_matrix_suite(void) {
  Suite* suite = suite_create("inverse_matrix");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, inverse_matrix_null_pointers);
  tcase_add_test(tc_core, inverse_matrix_invalid_matrices);
  tcase_add_test(tc_core, inverse_matrix_non_square);
  tcase_add_test(tc_core, inverse_matrix_zero_determinant);
  tcase_add_test(tc_core, inverse_matrix_readme_example);
  tcase_add_test(tc_core, inverse_matrix_1x1);
  tcase_add_test(tc_core, inverse_matrix_2x2);
  tcase_add_test(tc_core, inverse_matrix_fractional);
  suite_add_tcase(suite, tc_core);

  return suite;
}
