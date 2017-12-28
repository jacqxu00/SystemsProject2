#include "battleship.h"

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

struct aircraft *create_aircraft (char *name, int size) {
	struct aircraft *A = (struct aircraft *)malloc(sizeof(struct aircraft));
	strcpy(A->name, name);
	A->length = size;
	return A;
}
struct battleship *create_battleship (char *name, int size) {
	struct battleship *B = (struct battleship *)malloc(sizeof(struct battleship));
	strcpy(B->name, name);
	B->length = size;
	return B;
}
struct cruiser *create_cruiser (char *name, int size) {
	struct cruiser *C = (struct cruiser *)malloc(sizeof(struct cruiser));
	strcpy(C->name, name);
	C->length = size;
	return C;
}
struct submarine *create_submarine (char *name, int size) {
	struct submarine *S = (struct submarine *)malloc(sizeof(struct submarine));
	strcpy(S->name, name);
	S->length = size;
	return S;
}
struct destroyer *create_destroyer (char *name, int size) {
	struct destroyer *D = (struct destroyer *)malloc(sizeof(struct destroyer));
	strcpy(D->name, name);
	D->length = size;
	return D;
}

void initialize_board(char board[10][10]) {
  int i;
  for (i = 0; i < 10; i++) {
    memcpy(board[i],"..........",sizeof(".........."));
  }
}

void print_board(char board[10][10]) {
  int r;
  for (r = 0; r < 10; r++) {
    printf("%d ", r);
    int c;
    for (c = 0; c < 10; c++) {
      printf("%c ", board[r][c]);
    }
    printf("\n");
  }
}

void display(char h_board[10][10], char o_board[10][10]) {

    printf("\nHOME TERRITORY:\n");
    printf("  A B C D E F G H I J\n");
    print_board(h_board);

    printf("\nOPPONENT TERRITORY:\n");
    printf("  A B C D E F G H I J\n");
    print_board(o_board);

}

int main() {

	struct aircraft *A = create_aircraft("A", 5);
	struct battleship *B = create_battleship("B", 4);
	struct cruiser *C = create_cruiser("C", 3);
	struct submarine *S = create_submarine("S", 3);
	struct destroyer *D = create_destroyer("D", 2);

  char home[10][10];
  char opponent[10][10];
  initialize_board(home);
  initialize_board(opponent);

	printf("Aircraft: %s, %d\n", A->name, A->length);
	printf("Battleship: %s, %d\n", B->name, B->length);
	printf("Cruiser: %s, %d\n", C->name, C->length);
	printf("Submarine: %s, %d\n", S->name, S->length);
	printf("Destroyer: %s, %d\n", D->name, D->length);

	display(home, opponent);

}
