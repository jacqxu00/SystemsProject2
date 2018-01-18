all: battleship.o
	gcc -o battleship battleship.o

run: all
	./battleship

clean:
	rm -rf battleship

battleship.o: battleship.c battleship.h
	gcc -c battleship.c

compile_debug: battleship.c battleship.h
	gcc -g -o battleship_debug battleship.c

run_debug_valgrind: compile_debug
	valgrind --leak-check=yes ./battleship_debug

run_debug_gdb: compile_debug
	gdb battleship_debug
