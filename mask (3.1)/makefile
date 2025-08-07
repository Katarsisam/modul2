CFLAGS = -Wall -Wextra -std=c11 -g

all: clean run

mask : mask.o
	gcc $(CFLAGS) $< -o $@
	
run: mask 
	./mask 
	

clean:
	rm -f *.o mask *.txt

.PHONY: mask clean