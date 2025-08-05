SHELL = /bin/sh

CFLAGS = -Wall -Wextra -std=c11 -g -fPIC
LDFLAGS = -lcheck -lsubunit -lm
OS_NAME = $(shell uname)

# Object files
UTILS_SRC = $(wildcard utils/*.c)
UTILS_OBJ = $(UTILS_SRC:.c=.o)

ifeq ($(OS_NAME),Linux)
OPEN = xdg-open
endif

ifeq ($(OS_NAME),Darwin)
OPEN = open
endif

.PHONY: all clean clear install run libmaker

all: clear install

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

libs_a/libph.a: $(UTILS_OBJ) # Static library
	mkdir -p libs_a
	ar rcs $@ $^

libs_so/libph.so: $(UTILS_OBJ) # Shared library
	mkdir -p libs_so
	gcc -shared -o $@ $^

libmaker: clean libs_a/libph.a libs_so/libph.so
	mkdir -p build
	mv utils/*.o build

install: libmaker
	# Static version
	gcc $(CFLAGS) PhoneBook1.c -Llibs_a -lph -lncurses $(LDFLAGS) -o build/PhoneBook1X1
	# Dynamic version
	gcc $(CFLAGS) PhoneBook1.c -Llibs_so -lph -lncurses $(LDFLAGS) -Wl,-rpath=./libs_so -o build/PhoneBook1X2

runX1: install
	build/PhoneBook1X1
runX2: install
	build/PhoneBook1X2

clean:
	rm -rf *.o utils/*.o libs_so libs_a build

clear:
	clear