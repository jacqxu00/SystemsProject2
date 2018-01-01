#include "battleship.h"

struct aircraft {
  char name;
  int length;
  char coor[256];
};
struct battleship {
  char name;
  int length;
  char coor[256];
};
struct cruiser {
  char name;
  int length;
  char coor[256];
};
struct submarine {
  char name;
  int length;
  char coor[256];
};
struct destroyer {
  char name;
  int length;
  char coor[256];
};

struct aircraft *create_aircraft (char name, int size) {
  struct aircraft *A = (struct aircraft *)malloc(sizeof(struct aircraft));
  A->name = name;
  A->length = size;
  return A;
}
struct battleship *create_battleship (char name, int size) {
  struct battleship *B = (struct battleship *)malloc(sizeof(struct battleship));
  B->name = name;
  B->length = size;
  return B;
}
struct cruiser *create_cruiser (char name, int size) {
  struct cruiser *C = (struct cruiser *)malloc(sizeof(struct cruiser));
  C->name = name;
  C->length = size;
  return C;
}
struct submarine *create_submarine (char name, int size) {
  struct submarine *S = (struct submarine *)malloc(sizeof(struct submarine));
  S->name = name;
  S->length = size;
  return S;
}
struct destroyer *create_destroyer (char name, int size) {
  struct destroyer *D = (struct destroyer *)malloc(sizeof(struct destroyer));
  D->name = name;
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

void parse_placement(char * ship_p, char * col_p, int * row_p, char * dir_p){
  char buffer[256]; //should I limit it to 7 chars?

  printf("\nSetup Phase: \n\nTo place a ship, enter the following, each separated by a space: \n1. the letter representing the ship \n\tA: aircraft, size 5 \n\tB: battleship, size 4 \n\tC: cruiser, size 3 \n\tS: submarine, size 3\n\tD: destroyer, size 2\n2. the letter representing the column\n3. the digit representing the row\n4. the letter representing the direction \n\tLeft: L \n\tRight: R \n\tUp: U \n\tDown: D \nFor example: S A 0 D will place a submarine occupying A,0 A,1 A,2 \n\nEnter ship, column, row, and direction: ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  //for testing
  printf("Player Input: %s \n", buffer);
  sscanf(buffer, "%c %c %d %c", ship_p, col_p, row_p, dir_p);
	
}

int placement_valid(char ship, char col, int row, char dir){
  //catch possible out-of-bound or overlapping errors
  //invalid char for ship or dir

  if(ship != 'A' && ship != 'B' && ship != 'C' && ship != 'S' && ship != 'D'){
    printf("Invalid ship \n");
    return 0;
  }
  if(dir != 'L' && dir != 'R' && dir != 'U' && dir != 'D'){
    printf("Invalid direction \n");
    return 0;
  }

  //ship placed

  

  //any of ship's coordinates out-of-bounds or overlapping placed ship

  return 1;
}

void place_ship(char ship, char col, int row, char dir){
  
}

int main() {

  //setup

  struct aircraft *A = create_aircraft('A', 5);
  struct battleship *B = create_battleship('B', 4);
  struct cruiser *C = create_cruiser('C', 3);
  struct submarine *S = create_submarine('S', 3);
  struct destroyer *D = create_destroyer('D', 2);

  char home[10][10];
  char opponent[10][10];
  initialize_board(home);
  initialize_board(opponent);

  printf("Aircraft: %c, %d\n", A->name, A->length);
  printf("Battleship: %c, %d\n", B->name, B->length);
  printf("Cruiser: %c, %d\n", C->name, C->length);
  printf("Submarine: %c, %d\n", S->name, S->length);
  printf("Destroyer: %c, %d\n", D->name, D->length);

  //placement phase 

  char ship;
  char col;
  int row;
  char dir;
  int ships_placed = 0;

  while(ships_placed < 5){
    display(home, opponent);
    parse_placement(&ship, &col, &row, &dir);
    //for testing
    printf("Parsed Input: \n\tship: %c \n\tcol: %c \n\trow: %d \n\tdir: %c \n", ship, col, row, dir);
    if(placement_valid(ship, col, row, dir)){
      place_ship(ship, col, row, dir);
      ships_placed++;
    }
  }

  //playing phase

  return 0;
}
