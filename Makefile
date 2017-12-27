all: battleship.c
	gcc -o run battleship.c

run: all
	./run

clean: 
	rm run
	rm a.out
