#include <check.h>

Suite* create_matrix_suite(void);
Suite* remove_matrix_suite(void);
Suite* eq_matrix_suite(void);
Suite* sum_matrix_suite(void);
Suite* sub_matrix_suite(void);
Suite* mult_number_suite(void);
Suite* mult_matrix_suite(void);
Suite* transpose_suite(void);
Suite* determinant_suite(void);
Suite* calc_complements_suite(void);
Suite* inverse_matrix_suite(void);

int main(void) {
  int failed = 0;
  SRunner* runner = srunner_create(create_matrix_suite());

  srunner_add_suite(runner, remove_matrix_suite());
  srunner_add_suite(runner, eq_matrix_suite());
  srunner_add_suite(runner, sum_matrix_suite());
  srunner_add_suite(runner, sub_matrix_suite());
  srunner_add_suite(runner, mult_number_suite());
  srunner_add_suite(runner, mult_matrix_suite());
  srunner_add_suite(runner, transpose_suite());
  srunner_add_suite(runner, determinant_suite());
  srunner_add_suite(runner, calc_complements_suite());
  srunner_add_suite(runner, inverse_matrix_suite());

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed == 0 ? 0 : 1;
}
