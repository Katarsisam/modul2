SHELL = /bin/sh

CFLAGS = -Wall -Wextra -std=c11 -g 
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


libmaker: clean libs_a/libph.a
	mkdir -p obj build
	mv utils/*.o obj

install: libmaker
	# Static version
	gcc $(CFLAGS) PhoneBook1.c -Llibs_a -lph $(LDFLAGS) -o build/PhoneBook1X1
	
runX1: install
	build/PhoneBook1X1


clean:
	rm -rf *.o utils/*.o libs_a build obj

clear:
	clear