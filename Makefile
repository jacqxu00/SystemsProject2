all: networking.o battleship.o
	gcc -o battleship networking.o battleship.o

run: all
	./battleship

run_1: all
	./battleship 1

run_2: all
	./battleship 2

clean:
	rm -rf battleship

networking.o: networking.c battleship.h
	gcc -c networking.c

battleship.o: battleship.c battleship.h
	gcc -c battleship.c

compile_debug: networking.c battleship.c battleship.h
	gcc -g -o battleship_debug networking.c battleship.c

run_debug_valgrind: compile_debug
	valgrind --leak-check=yes ./battleship_debug

run_valgrind_1: compile_debug
	valgrind --leak-check=yes ./battleship_debug 1

run_valgrind_2: compile_debug
	valgrind --leak-check=yes ./battleship_debug 2

run_debug_gdb: compile_debug
	gdb battleship_debug

run_gdb_1: compile_debug
	gdb battleship_debug 1

run_gdb_2: compile_debug
	gdb battleship_debug 2
