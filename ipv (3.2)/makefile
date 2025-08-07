CFLAGS = -Wall -Wextra -std=c11 -g

all: clean ipv

ipv : ipv.o
	gcc $(CFLAGS) $< -o $@
	

clean:
	rm -f *.o ipv *.txt

.PHONY: ipv clean