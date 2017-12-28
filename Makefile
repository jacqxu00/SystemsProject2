all: battleship.c
	gcc -o battleship battleship.c

run: all
	./battleship

clean:
	rm -rf battleship
