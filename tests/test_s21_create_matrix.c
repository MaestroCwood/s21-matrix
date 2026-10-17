#include <check.h>

#include "../s21_matrix.h"

START_TEST(create_matrix_null_result) {
  ck_assert_int_eq(s21_create_matrix(2, 2, NULL), 1);
}
END_TEST

START_TEST(create_matrix_invalid_size) {
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(0, 2, &result), 1);
  ck_assert_int_eq(s21_create_matrix(2, -1, &result), 1);
  ck_assert_int_eq(s21_create_matrix(-3, 3, &result), 1);
}
END_TEST

START_TEST(create_matrix_success_sizes) {
  s21_matrix m1 = {0};
  s21_matrix m2 = {0};
  s21_matrix m3 = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &m1), 0);
  ck_assert_int_eq(m1.rows, 1);
  ck_assert_int_eq(m1.columns, 1);
  ck_assert_ptr_nonnull(m1.matrix);

  ck_assert_int_eq(s21_create_matrix(2, 2, &m2), 0);
  ck_assert_int_eq(m2.rows, 2);
  ck_assert_int_eq(m2.columns, 2);

  ck_assert_int_eq(s21_create_matrix(2, 3, &m3), 0);
  ck_assert_int_eq(m3.rows, 2);
  ck_assert_int_eq(m3.columns, 3);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m3);
}
END_TEST

START_TEST(create_matrix_zero_initialized) {
  s21_matrix result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &result), 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq(result.matrix[i][j], 0.0);
    }
  }
  s21_remove_matrix(&result);
}
END_TEST

Suite* create_matrix_suite(void) {
  Suite* suite = suite_create("create_matrix");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, create_matrix_null_result);
  tcase_add_test(tc_core, create_matrix_invalid_size);
  tcase_add_test(tc_core, create_matrix_success_sizes);
  tcase_add_test(tc_core, create_matrix_zero_initialized);
  suite_add_tcase(suite, tc_core);

  return suite;
}
