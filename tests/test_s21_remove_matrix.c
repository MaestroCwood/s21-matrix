#include <check.h>

#include "../s21_matrix.h"

START_TEST(remove_matrix_null_pointer) {
  s21_remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(remove_matrix_frees_memory) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &matrix), 0);
  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
  ck_assert_int_eq(matrix.rows, 0);
  ck_assert_int_eq(matrix.columns, 0);
}
END_TEST

START_TEST(remove_matrix_empty_struct) {
  s21_matrix matrix = {0};

  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

START_TEST(remove_matrix_repeated_call) {
  s21_matrix matrix = {0};

  ck_assert_int_eq(s21_create_matrix(3, 2, &matrix), 0);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix);
  ck_assert_ptr_null(matrix.matrix);
}
END_TEST

Suite* remove_matrix_suite(void) {
  Suite* suite = suite_create("remove_matrix");
  TCase* tc_core = tcase_create("core");

  tcase_add_test(tc_core, remove_matrix_null_pointer);
  tcase_add_test(tc_core, remove_matrix_frees_memory);
  tcase_add_test(tc_core, remove_matrix_empty_struct);
  tcase_add_test(tc_core, remove_matrix_repeated_call);
  suite_add_tcase(suite, tc_core);

  return suite;
}
