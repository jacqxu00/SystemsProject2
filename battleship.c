#include "battleship.h"

void display() {

    printf("\nYOUR BOARD:                OPPONENT BOARD:\n\n");
    printf("  A B C D E F G H I J        A B C D E F G H I J\n");
    
    int i; 
    for (i = 0; i < 10; i++) {
        printf("%d ", i); //print row number
        // print i-th line of txt file
        printf("\n");
    }
}

struct aircraft {
	char name[256];
	int length;
	char coor[256];
};
struct battleship {
	char name[256];
	int length;
	char coor[256];
};
struct cruiser {
	char name[256];
	int length;
	char coor[256];
};
struct submarine {
	char name[256];
	int length;
	char coor[256];
};
struct destroyer {
	char name[256];
	int length;
	char coor[256];
};

void setup () {
	strcpy(A.name, "A");
	A.length = 5;
	
	strcpy(B.name, "B");
	B.length = 4;
	
	strcpy(C.name, "C");
	C.length = 3;
	
	strcpy(S.name, "S");
	S.length = 3;
	
	strcpy(D.name, "D");
	D.length = 2;
}

void printAircraft (struct aircraft a) {
	printf("%s, %d", a.name, a.length);
}

int main() {

	struct aircraft A;
	struct battleship B;
  struct cruiser C;
	struct submarine S;
	struct destroyer D;
	
	setup();
	
	printAircraft (A);
	
	display();

}
