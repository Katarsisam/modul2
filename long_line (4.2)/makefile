CFLAGS = -Wall -Wextra -std=c11 -g

all: clean run

longline: longline.o
	gcc $(CFLAGS) $< -o $@
	
run: longline 
	./longline 
	

clean:
	rm -f *.o longline *.txt

.PHONY: longline clean