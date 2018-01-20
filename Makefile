all: networking.o battleship.o
	gcc -o battleship networking.o battleship.o

run: all
	./battleship

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

run_debug_gdb: compile_debug
	gdb battleship_debug
