
SHELL = /bin/sh

CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lcheck -lsubunit -lm
U_SRC := $(wildcard utils/*.c)
LIB := $(addprefix lib,$(notdir $(U_SRC:.c=.so)))
LNAME :=  $(notdir $(basename $(U_SRC)))
GCOV_FLAGS = --coverage -fprofile-arcs -ftest-coverage

OS_NAME = $(shell uname)

ifeq ($(OS_NAME),Linux)
OPEN = xdg-open
endif

ifeq ($(OS_NAME),Darwin)
OPEN = open
endif

.PHONY: all clean

all: clear install

%.o: utils/%.c
	gcc $(CFLAGS) -c $< -fPIC -o $@

lib%.so: %.o
	gcc -shared -o $@ $<
	

libmaker: clean $(LIB)
	mkdir -p build
	mkdir -p libs
	mv *.o build | mv *.so libs

install: libmaker
	gcc $(CFLAGS) -Wl,-rpath=./libs -o build/Calculator Calculator.c -L./libs $(addprefix -l,$(LNAME)) $(LDFLAGS) 

run: install
	build/Calculator

uninstall:
	rm -rf build

clean:
	rm -rf build gcov libs
	
test: libmaker
	gcc $(CFLAGS) -Wl,-rpath=./libs unit_test/unit_test.c -L./libs $(addprefix -l,$(LNAME)) $(LDFLAGS) -o unit_test/unit_test
	unit_test/unit_test

gcov_report: libmaker
	mkdir -p gcov
	gcc $(CFLAGS) $(GCOV_FLAGS) unit_test/unit_test.c $(U_SRC)  $(LDFLAGS) -o gcov/gcov_test
	gcov/gcov_test
	lcov --capture --directory . --output-file gcov/coverage.info
	lcov --remove gcov/coverage.info '*unit_test/*' --output-file gcov/coverage.info
	genhtml -o gcov/report gcov/coverage.info
	#$(OPEN) gcov/report/brick_game/tetris/index.html

clang_format:

	clang-format -i *.c *.h
	clang-format -i unit_test/*.c unit_test/*.h
	clang-format -i libs/*.c libs/*.h
clang_check:
	clang-format -n *.c *.h
	clang-format -n unit_test/*.c unit_test/*.h
	clang-format -n libs/*.c libs/*.h

valgrind: test
	cd unit_test && valgrind --tool=memcheck --leak-check=yes ./unit_test

clear:
	clear
