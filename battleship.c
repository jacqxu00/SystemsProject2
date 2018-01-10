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
  printf("            %d ", row);
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
  printf("\n            HOME TERRITORY:             OPPONENT TERRITORY:\n");
  printf("              A B C D E F G H             A B C D E F G H\n");
  int i;
  for (i = 0; i < 8; i++) {
    print_board(home, opp, i);
  }

}

int placement_valid (char ship, char col, char row, char dir, struct board * home, struct board * opp, char shipP[256]) {

  // invalid char for ship
  if (ship != 'A' && ship != 'B' && ship != 'C' && ship != 'S' && ship != 'D') {
    display(home, opp);
    printf("\nERROR: Invalid ship, please try again. \n");
    return 0;
  }
  // invalid char for column
  if (col < 'A' || col > 'H') {
    display(home, opp);
    printf("\nERROR: Invalid column, please try again. \n");
    return 0;
  }
  // invalid int for row
  if (row < '0' || row > '7') {
    display(home, opp);
    printf("\nERROR: Invalid row, please try again. \n");
    return 0;
  }
  // invalid char for dir
  if (dir != 'L' && dir != 'R' && dir != 'U' && dir != 'D') {
    display(home, opp);
    printf("\nERROR: Invalid direction, please try again. \n");
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
      display(home, opp);
      printf("\nERROR: Overlapping ships, please try again.\n");
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
      display(home, opp);
      printf("\nERROR: Out-of-bounds, please try again.\n");
      return 0;
    }
  }
  else if (dir == 'R') {
    if (!(c + (len - 1) <= 9)) {
      display(home, opp);
      printf("\nERROR: Out-of-bounds, please try again.\n");
      return 0;
    }
  }
  else if (dir == 'U') {
    if (!(r - (len - 1) >= 0)) {
      display(home, opp);
      printf("\nERROR: Out-of-bounds, please try again.\n");
      return 0;
    }
  }
  else {
    if (!(r + (len - 1) <= 9)) {
      display(home, opp);
      printf("\nERROR: Out-of-bounds, please try again.\n");
      return 0;
    }
  }

  // ship already placed
  if (ship == shipP[0] || ship == shipP[1] || ship == shipP[2] || ship == shipP[3] || ship == shipP[4]) {
    display(home, opp);
    printf("\nERROR: Ship already placed, please input another ship. \n");
    return 0;
  }

  return 1;

}

int parse_placement (char * ship_p, char * col_p, char * row_p, char * dir_p, struct board * home, struct board * opp, char shipP[256]) {

	char buffer[256];

  // print out placed ships
  printf("\n\nShips left to place: ");
    //ship + size


  printf("\n\nEnter ship (A, B, C, D, S): ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  int scanned = sscanf(buffer, "%c", ship_p); //won't make use of extra tokens

  if (scanned != 1){
    display(home, opp);
    printf("\nERROR: Ship input invalid, please try again. \n");
    return 0;
  }

  printf("Enter coordinate (e.g. A0): ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  scanned = sscanf(buffer, "%c%c", col_p, row_p);

  if (scanned != 2){
    display(home, opp);
    printf("\nERROR: Coordinate input invalid, please try again. \n");
    return 0;
  }

  printf("Enter direction (L, R, U, D): ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  scanned = sscanf(buffer, "%c", dir_p);

  if (scanned != 1){
    display(home, opp);
    printf("\nERROR: Direction input invalid, please try again. \n");
    return 0;
  }

  return placement_valid(*ship_p, *col_p, *row_p, *dir_p, home, opp, shipP);

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
  for (r = 0; r < 8; r++) {
    int c;
    for (c = 0; c < 8; c++) {
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
  printf("\e[8;20;68;t");

  //instructions
  int start_setup = 0;
  char buffer1[256];
  char buffer2[256];

  pretty_spacing(30);
  printf("\n\n\nHello, and welcome to Battleship! \nFirst, we will begin with a setup phase (where you will be asked to place your ships), then we will continue to the playing phase (where\nyou compete with your opponent). \nAll standard Battleship rules apply, but we will explain the syntax of our terminal game. \n\nPress enter to continue.\n");
  fgets(buffer1, sizeof(buffer1), stdin);

  if (sizeof(buffer1)>0) {
    pretty_spacing(30);
    printf("\nSETUP PHASE: \n\nYou will be asked to input the ship, the starting coordinates of the\nlocation, and the direction in which it extends.\n1. the available ships \n\tA: aircraft, size 5 \n\tB: battleship, size 4 \n\tC: cruiser, size 3 \n\tS: submarine, size 3 \n\tD: destroyer, size 2 \n2. the letter and digit corresponding to the column and the row \n4. the letter representing the direction \n\tL: left \n\tR: right \n\tU: up \n\tD: down \nFor example: S A0 D will place a submarine occupying A0, A1, and A2\n\nPress enter to continue.\n");
    fgets(buffer2, sizeof(buffer2), stdin);
  }

  if (sizeof(buffer2)>0) {
    start_setup++;
  }

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

  while(ships_placed < 5 && start_setup){
    display(home, opponent);
    while(!parse_placement(&ship, &col, &row, &dir, home, opponent, shipPlace)){
    }
    place_ship(ship, col, row, dir, home, shipPlace);
    ships_placed++;
  }

  //receive opponent board

  //playing instructions
  int start_play = 0;
  char buffer3[256];

  pretty_spacing(30);
  printf("\nPLAYING PHASE: \n\nYou will be asked to input the coordinates of the location you would\nlike to send a missile to. \n\n\tFor example: A0 \nHere is what the board display means: \n\t. (empty slot) \n\t* (missed ship) \n\tH (hit ship)\n\nPress enter to continue.\n");
  fgets(buffer3, sizeof(buffer3), stdin);

  if (sizeof(buffer3)>0) {
    start_play++;
  }

  //playing phase
  //while (!game_over(home, opponent) && start_play) {
  while (1) {
    display(home, opponent);
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
