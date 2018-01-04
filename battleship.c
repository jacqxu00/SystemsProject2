#include "battleship.h"

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

void encrypt_board(char board[10][10]) {
  int r, c;
  for (r = 0; r < 10; r++) {
    for (c = 0; c < 10; c++) {
      char c = board[r][c] - 'A';
      if (c >= 0 && c <= 25) {
        board[r][c] = '.';
      }
    }
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

int placement_valid(char ship, char col, char row, char dir, char shipP[256]){

  // invalid char for ship
  if(ship != 'A' && ship != 'B' && ship != 'C' && ship != 'S' && ship != 'D'){
    printf("\nInvalid ship, please try again. \n");
    return 0;
  }
  // invalid char for column
  if(col < 'A' || col > 'J'){
    printf("\nInvalid column, please try again. \n");
    return 0;
  }
  // invalid int for row
  if(row < '0' || row > '9'){
    printf("\nInvalid row, please try again. \n");
    return 0;
  }
  // invalid char for dir
  if(dir != 'L' && dir != 'R' && dir != 'U' && dir != 'D'){
    printf("\nInvalid direction, please try again. \n");
    return 0;
  }

  //FIX catch possible out-of-bound or overlapping errors

  // ship already placed
	if (ship == shipP[0] || ship == shipP[1] || ship == shipP[2] || ship == shipP[3] || ship == shipP[4]) {
		printf("\nShip already placed, please input another ship. \n");
		return 0;
	}

  return 1;
}

int parse_placement(char * ship_p, char * col_p, char * row_p, char * dir_p, char shipP[256]){
  char buffer[256]; 

  printf("\nSetup Phase: \n\nTo place a ship, enter the following, each separated by a space: \n1. the letter representing the ship \n\tA: aircraft, size 5 \n\tB: battleship, size 4 \n\tC: cruiser, size 3 \n\tS: submarine, size 3 \n\tD: destroyer, size 2 \n2. the letter representing the column \n3. the digit representing the row \n4. the letter representing the direction \n\tLeft: L \n\tRight: R \n\tUp: U \n\tDown: D \nFor example: S A 0 D will place a submarine occupying A,0 A,1 A,2");
	
	// print out placed ships
	printf("\n\nShips already placed: ");
	int i;
  for (i = 0; i < 5; i++) {
    printf("%c ", shipP[i]);
  }
	
	printf("\n\nEnter ship, column, row, and direction: ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  //for testing
  printf("\nPlayer Input: %s \n", buffer);
  int scanned = sscanf(buffer, "%c %c %c %c", ship_p, col_p, row_p, dir_p); //won't make use of extra tokens
  //for testing
  printf("\nParsed Input: \n\tship: %c \n\tcol: %c \n\trow: %c \n\tdir: %c \n", *ship_p, *col_p, *row_p, *dir_p);
	
  //FIX if there are < or > 4 inputs
  if(scanned < 4){ 
    printf("\nMissing one or more instructions, please try again. \n");
    return 0;
  }

  return placement_valid(*ship_p, *col_p, *row_p, *dir_p, shipP);
}

void place_ship(char ship, char col, char row, char dir, char board[10][10], char shipP[256]){

  //set up direction
  int x, y;
  if (dir == 'L') {
    x = -1; y = 0;
  }
  else if (dir == 'R') {
    x = 1; y = 0;
  }
  else if (dir == 'U') {
    x = 0; y = -1;
  }
  else {
    x = 0; y = 1;
  }

  //set up ship length
  int len;
  if (ship == 'A') {len = 5;}
  else if (ship == 'B') {len = 4;}
  else if (ship == 'C' || ship == 'S') {len = 3;}
  else {len = 2;}

  //set up row and col
  int c = col - 'A';
  int r = row - '0';

  //changing variables in char**
  while (len) {
    board[r][c] = ship;
    r = r+y;
    c = c+x;
    len--;
  }
	
	//adding ship to char array of placed ships
  if (ship == 'A') {shipP[0] = 'A';}
  else if (ship == 'B') {shipP[1] = 'B';}
	else if (ship == 'C') {shipP[2] = 'C';}
  else if (ship == 'S') {shipP[3] = 'S';}
  else {shipP[4] = 'D';}

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
	char shipPlace[256];
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
  char row;
  char dir;
  int ships_placed = 0;

  while(ships_placed < 5){
    display(home, opponent);
    while(!parse_placement(&ship, &col, &row, &dir, shipPlace)){
      
    }
    //if(placement_valid(ship, col, row, dir)){
    place_ship(ship, col, row, dir, home, shipPlace);
    printf("\nSuccesful placement!\n");
    ships_placed++;
    //}
  }

  //playing phase

  return 0;
}
