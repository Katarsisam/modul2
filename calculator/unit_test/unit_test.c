#include "unit_test.h"

START_TEST(test_add) {
  ck_assert_int_eq(add(2, 3), 5);
  ck_assert_int_eq(add(-1, 1), 0);
  ck_assert_int_eq(add(0, 0), 0);
}
END_TEST
START_TEST(test_subtract) {
  ck_assert_int_eq(subtract(3, 2), 1);
  ck_assert_int_eq(subtract(-1, 1), -2);
  ck_assert_int_eq(subtract(0, 0), 0);
}
END_TEST
START_TEST(test_multiply) {
  ck_assert_int_eq(multiply(3, 2), 6);
  ck_assert_int_eq(multiply(-1, 1), -1);
  ck_assert_int_eq(multiply(0, 0), 0);
}
END_TEST
START_TEST(test_divide) {
  ck_assert_int_eq(divide(6, 2), 3);
  ck_assert_int_eq(divide(-1, 1), -1);
  ck_assert_int_eq(divide(2, 0), 0);
}
END_TEST
START_TEST(test_power) {
  ck_assert_int_eq(power(6, 2), 36);
  ck_assert_int_eq(power(-1, 1), -1);
  ck_assert_int_eq(power(2, 0), 1);
}
END_TEST
START_TEST(test_square_root) {
  ck_assert_int_eq(square_root(4), 2);
  ck_assert_int_eq(square_root(1), 1);
  ck_assert_int_eq(square_root(-1), 0);
}
END_TEST
START_TEST(test_add_command_1) {
  Command *commands = NULL;
  int command_count = 0;
  double a = 2, b = 3;
  add_command(&commands, &command_count, "add", "Сложение двух чисел", add, 2);
  ck_assert_int_eq(commands->func(a, b), 5);
}
END_TEST

Suite *Calc_suite() {
  Suite *s = suite_create("Calc_suite");
  TCase *tc = tcase_create("Calc_tc");

  tcase_add_test(tc, test_add);
  tcase_add_test(tc, test_subtract);
  tcase_add_test(tc, test_multiply);
  tcase_add_test(tc, test_divide);
  tcase_add_test(tc, test_power);
  tcase_add_test(tc, test_square_root);
  tcase_add_test(tc, test_add_command_1);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  Suite *s = Calc_suite();
  SRunner *sr = srunner_create(s);
  int tf = 0;

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  tf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return tf > 0;
}