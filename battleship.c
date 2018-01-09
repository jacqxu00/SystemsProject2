#include "battleship.h"

void pretty_spacing(int x) {
  int i;
  for (i = 0; i < x; i ++) {
    printf("\n");
  }
}

void initialize_board (struct board * home) {
	int i, j;
  for (i = 0; i < home->rows; i++) {
		for (j = 0; j < home->cols; j++) {
    	home->board_[i][j] = '.';
		}
  }
}

void print_board (struct board * home, struct board * opp, int row) {

  //print home board row
  printf("    %d ", row);
  int c;
  for (c = 0; c < home->cols; c++) {
    printf("%c ", home->board_[row][c]);
  }
  printf("          ");

  //print opponent board row
  printf("%d ", row);
  int d;
  for (d = 0; d < opp->cols; d++) {
    int coor = opp->board_[row][d] - 'A';

    //hide location of unhit ship
    if (c >= 0 && c <= 25 && c !=7) {
      printf("%c ", '.');
    }

    //else print the character of the 2d array
    else {
      printf("%c ", opp->board_[row][c]);
    }

  }
  printf("\n");
}

void display (struct board * home, struct board * opp) {
  pretty_spacing(30);
  printf("\n    HOME TERRITORY:                 OPPONENT TERRITORY:\n");
  printf("      A B C D E F G H                 A B C D E F G H\n");
  int i;
  for (i = 0; i < 8; i++) {
    print_board(home, opp, i);
  }

}

int placement_valid (char ship, char col, char row, char dir, struct board * home, char shipP[256]) {

  // invalid char for ship
  if (ship != 'A' && ship != 'B' && ship != 'C' && ship != 'S' && ship != 'D') {
    printf("\nInvalid ship, please try again. \n");
    return 0;
  }
  // invalid char for column
  if (col < 'A' || col > 'H') {
    printf("\nInvalid column, please try again. \n");
    return 0;
  }
  // invalid int for row
  if (row < '0' || row > '7') {
    printf("\nInvalid row, please try again. \n");
    return 0;
  }
  // invalid char for dir
  if (dir != 'L' && dir != 'R' && dir != 'U' && dir != 'D') {
    printf("\nInvalid direction, please try again. \n");
    return 0;
  }

  //overlapping errors
  //set up direction
  int x = 0;
  int y = 0;
  if (dir == 'L') {x = -1;}
  else if (dir == 'R') {x = 1;}
  else if (dir == 'U') {y = -1;}
  else {y = 1;}

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
    if (home->board_[r][c] != '.') {
      printf("\nOverlapping error, please try again.\n");
      return 0;
    }
    r = r+y;
    c = c+x;
    len--;
  }

  //out-of-bound
  //set up row and col
  c = col - 'A';
  r = row - '0';

  // set up direction
  if (dir == 'L') {
    if (!(c - (len - 1) >= 0)) {
      printf("\nOut-of-bounds, please try again.\n");
      return 0;
    }
  }
  else if (dir == 'R') {
    if (!(c + (len - 1) <= 9)) {
      printf("\nOut-of-bounds, please try again.\n");
      return 0;
    }
  }
  else if (dir == 'U') {
    if (!(r - (len - 1) >= 0)) {
      printf("\nOut-of-bounds, please try again.\n");
      return 0;
    }
  }
  else {
    if (!(r + (len - 1) <= 9)) {
      printf("\nOut-of-bounds, please try again.\n");
      return 0;
    }
  }

  // ship already placed
  if (ship == shipP[0] || ship == shipP[1] || ship == shipP[2] || ship == shipP[3] || ship == shipP[4]) {
    printf("\nShip already placed, please input another ship. \n");
    return 0;
  }

  return 1;

}

int parse_placement (char * ship_p, char * col_p, char * row_p, char * dir_p, struct board * home, char shipP[256]) {

	char buffer[256];

  printf("\nSETUP PHASE: \n\nTo place a ship, enter the following, each separated by a space: \n1. the letter representing the ship \n\tA: aircraft, size 5 \n\tB: battleship, size 4 \n\tC: cruiser, size 3 \n\tS: submarine, size 3 \n\tD: destroyer, size 2 \n2. the letter representing the column \n3. the digit representing the row \n4. the letter representing the direction \n\tLeft: L \n\tRight: R \n\tUp: U \n\tDown: D \nFor example: S A 0 D will place a submarine occupying A,0 A,1 A,2");

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
  if (scanned < 4){
    printf("\nMissing one or more instructions, please try again. \n");
    return 0;
  }

  return placement_valid(*ship_p, *col_p, *row_p, *dir_p, home, shipP);

}

void place_ship (char ship, char col, char row, char dir, struct board * home, char shipP[256]){

  //set up direction
  int x = 0;
  int y = 0;
  if (dir == 'L') {x = -1;}
  else if (dir == 'R') {x = 1;}
  else if (dir == 'U') {y = -1;}
  else {y = 1;}

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
    home->board_[r][c] = ship;
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

int player_loss (struct board * home) {

  int ans = 1;
  int r;
  for (r = 0; r < 10; r++) {
    int c;
    for (c = 0; c < 10; c++) {
      if (!(home->board_[r][c] == '.' || home->board_[r][c] == '*' || home->board_[r][c] == 'H')) {
        ans = 0;
      }
    }
  }
  return ans;
}

int game_over (struct board * home, struct board * opp) {

  if (player_loss(home)) {return 1;}
  else if (player_loss(opp)) {return 2;}
  else {return 0;}

}

void attack (struct board * receive, char row, char col) {

  if (receive->board_[row][col] == '.') {
    receive->board_[row][col] = '*';
    printf("\nYou've missed. It is now your opponent's turn.\n");
  }

  else if (receive->board_[row][col] == '*' || receive->board_[row][col] == 'H') {
    printf("\nYou've already entered this coordinate. Please try again.\n");
  }

  else {
    receive->board_[row][col] = 'H';
    printf("\nYou've hit a ship! It is now your opponent's turn.\n");
  }
}

int main() {
  printf("\e[8;35;68;t");

  //setup
  struct aircraft *A = create_aircraft('A', 5);
  struct battleship *B = create_battleship('B', 4);
  struct cruiser *C = create_cruiser('C', 3);
  struct submarine *S = create_submarine('S', 3);
  struct destroyer *D = create_destroyer('D', 2);

  struct board *home = create_board(8, 8);
  struct board *opponent = create_board(8, 8);
  char shipPlace[256] = "     ";
  initialize_board(home);
  initialize_board(opponent);

  //placement phase
  char ship;
  char col;
  char row;
  char dir;
  int ships_placed = 0;

  while(ships_placed < 5){
    display(home, opponent);
    while(!parse_placement(&ship, &col, &row, &dir, home, shipPlace)){

    }
    //if(placement_valid(ship, col, row, dir, shipPlace)){
    place_ship(ship, col, row, dir, home, shipPlace);
    printf("\nSuccesful placement!\n");
    ships_placed++;
    //}
  }

  //playing phase
  while (!game_over(home, opponent)) {

  }

  //game over
  if (game_over(home, opponent) == 1) {
    printf("\nGAME OVER. You've lost.\n");
  }
  else if (game_over(home, opponent) == 2) {
    printf("\nCONGRATULATIONS! You've won!\n");
  }

  return 0;
}
