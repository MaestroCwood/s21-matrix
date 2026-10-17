CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS =
LIBS = -lcheck -lsubunit -lm -lpthread

UNAME_S := $(shell uname -s 2>/dev/null)
ifeq ($(UNAME_S),Darwin)
  LDFLAGS += -L/opt/homebrew/lib -L/usr/local/lib
  CFLAGS += -I/opt/homebrew/include -I/usr/local/include
  LIBS = -lcheck
endif
ifneq ($(filter MINGW% MSYS%,$(UNAME_S)),)
  LIBS = -lcheck
endif

LIB_SOURCES = s21_create_matrix.c \
              s21_remove_matrix.c \
              s21_eq_matrix.c \
              s21_sum_matrix.c \
              s21_sub_matrix.c \
              s21_mult_number.c \
              s21_mult_matrix.c \
              s21_transpose.c \
              s21_determinant.c \
              s21_calc_complements.c \
              s21_inverse_matrix.c \
              s21_matrix_helpers.c

TEST_SOURCES = tests/test_s21_create_matrix.c \
               tests/test_s21_remove_matrix.c \
               tests/test_s21_eq_matrix.c \
               tests/test_s21_sum_matrix.c \
               tests/test_s21_sub_matrix.c \
               tests/test_s21_mult_number.c \
               tests/test_s21_mult_matrix.c \
               tests/test_s21_transpose.c \
               tests/test_s21_determinant.c \
               tests/test_s21_calc_complements.c \
               tests/test_s21_inverse_matrix.c \
               tests/tests_runner.c

LIB_OBJECTS = $(LIB_SOURCES:.c=.o)
TEST_TARGET = test.out
REPORT_DIR = report

.PHONY: all clean test gcov_report s21_matrix.a

all: s21_matrix.a $(TEST_TARGET)

s21_matrix.a: $(LIB_OBJECTS)
	ar rcs s21_matrix.a $(LIB_OBJECTS)
	ranlib s21_matrix.a

$(TEST_TARGET): $(TEST_SOURCES) s21_matrix.a
	$(CC) $(CFLAGS) $(TEST_SOURCES) s21_matrix.a -o $(TEST_TARGET) $(LDFLAGS) $(LIBS)

%.o: %.c s21_matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SOURCES) $(LIB_SOURCES) -o $(TEST_TARGET) $(LDFLAGS) $(LIBS)
	./$(TEST_TARGET)
	lcov -t "gcov_report" -o coverage.info -c -d . --no-external
	genhtml -o $(REPORT_DIR) coverage.info
	@echo "Gcov report: $(REPORT_DIR)/index.html"

clean:
	rm -rf $(LIB_OBJECTS) tests/*.o s21_matrix.a $(TEST_TARGET) *.gcno *.gcda *.gcov coverage.info $(REPORT_DIR)
