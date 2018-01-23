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

int placement_valid (char ship, char col, char row, char dir, struct board * home, struct board * opp, char shipP[6][13]) {

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
    if (!(c + (len - 1) <= 7)) {
      display(home, opp);
      printf("\nERROR: Out-of-bounds, please try again.\n");
      return 0;
    }
  }
  else if (dir == 'U') {
    if (!(r - (len - 1) >= 7)) {
      display(home, opp);
      printf("\nERROR: Out-of-bounds, please try again.\n");
      return 0;
    }
  }
  else {
    if (!(r + (len - 1) <= 7)) {
      display(home, opp);
      printf("\nERROR: Out-of-bounds, please try again.\n");
      return 0;
    }
  }

  // ship already placed
  if (ship != shipP[0][0] && ship != shipP[1][0] && ship != shipP[2][0] && ship != shipP[3][0] && ship != shipP[4][0]) {
    display(home, opp);
    printf("\nERROR: Ship already placed, please input another ship. \n");
    return 0;
  }

  return 1;

}

int missile_valid (char col, char row, struct board * home, struct board * opp){
  int c = col - 'A';
  int r = row - '0';
  if (c < 0 || c > 7 || r < 0 || r > 9) {
    display(home, opp);
    printf("\nERROR: Coordinate out of bounds, please try again.\n");
    return 0;
  }
  return 1;
}

int parse_ship (char * ship_p, char * col_p, char * row_p, char * dir_p, struct board * home, struct board * opp, char shipP[6][13]) {

  char buffer[256];

  // print out available ships
  printf("\n\nShips left to place: ");
  int i;
  for (i = 0; i < 5; i++) {
    printf("%s\n\t\t     ", shipP[i]);
  }
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

void place_ship (char ship, char col, char row, char dir, struct board * home, char shipP[6][13]){

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
  if (ship == 'A') {strcpy(shipP[0], "");}
  else if (ship == 'B') {strcpy(shipP[1], "");}
  else if (ship == 'C') {strcpy(shipP[2], "");}
  else if (ship == 'S') {strcpy(shipP[3], "");}
  else {strcpy(shipP[4], "");}

}

int parse_missile (char * col_p, char * row_p, struct board * home, struct board * opp) {

  char buffer[256];

  printf("\n\nEnter a coordinate to hit (e.g. 'A0'): ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  int scanned = sscanf(buffer, "%c%c", col_p, row_p);

  if (scanned != 2){
    display(home, opp);
    printf("\nERROR: coordinate invalid, please try again. \n");
    return 0;
  }

  return missile_valid(*col_p, *row_p, home, opp);
}

void place_missile (char col, char row, struct board * opp) {

  if (opp->board_[row][col] == '.') {
    opp->board_[row][col] = '*';
    printf("\nYou've missed. It is now your opponent's turn.\n");
  }

  else if (opp->board_[row][col] == '*' || opp->board_[row][col] == 'H') {
    printf("\nYou've already entered this coordinate. Please try again.\n");
  }

  else {
    opp->board_[row][col] = 'H';
    printf("\nYou've hit a ship! It is now your opponent's turn.\n");
  }

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

int main(int argc, char ** argv) {

  //network setup
  int player_num;
  int listen_socket; //for player 1
  int client_socket; //for player 1
  int server_socket; //for player 2
  char * address = argv[2];
  printf("%s", address);
  
  player_num = player(argc, argv);
  //close(server_socket);
  //close(listen_socket);
  //close(client_socket);
  //wait for both to be ready first?
  connecting(player_num, address, &listen_socket, &client_socket, &server_socket);
	
  /*
    printf("TESTING\n");
	
    char buffer[256];
	
    if (player_num == 2) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
    }
    else {
    while(read(client_socket, buffer, sizeof(buffer))) {
    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    write(client_socket, buffer, sizeof(buffer));
			
    return 0;
    }
    }
    close(client_socket);
    //close(server_socket);
    //close(listen_socket);
    */

  printf("\e[8;21;68;t");

  //instructions
  int start_setup = 0;
  char buffer1[256];
  char buffer2[256];

  pretty_spacing(30);
  printf(WELCOME_MSG);
  fgets(buffer1, sizeof(buffer1), stdin);

  if (sizeof(buffer1)>0) {
    pretty_spacing(30);
    printf(SETUP_INSTRUCTIONS);
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
  char shipPlace[6][13];
  strcpy(shipPlace[0], "A (size 5)");
  strcpy(shipPlace[1], "B (size 4)");
  strcpy(shipPlace[2], "C (size 3)");
  strcpy(shipPlace[3], "S (size 3)");
  strcpy(shipPlace[4], "D (size 2)");

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
    while(!parse_ship(&ship, &col, &row, &dir, home, opponent, shipPlace)){
    }
    place_ship(ship, col, row, dir, home, shipPlace);
    ships_placed++;
  }

  //receive opponent board
  char bufferSend[8][8];
  int i, j;
  for (i = 0; i < home->rows; i++) {
    for (j = 0; j < home->cols; j++) {
      bufferSend[i][j] = home->board_[i][j];
    }
  }
  if (player_num == 1) {
    write(client_socket, bufferSend, sizeof(bufferSend));
    read(client_socket, bufferSend, sizeof(bufferSend));
  } else {
    write(server_socket, bufferSend, sizeof(bufferSend));
    read(server_socket, bufferSend, sizeof(bufferSend));
  }
	
  for (i = 0; i < home->rows; i++) {
    for (j = 0; j < home->cols; j++) {
      opponent->board_[i][j] = bufferSend[i][j];
    }
  }

  //playing instructions
  int start_play = 0;
  char buffer3[256];

  pretty_spacing(30);
  printf(PLAYING_INSTRUCTIONS);
  fgets(buffer3, sizeof(buffer3), stdin);

  if (sizeof(buffer3)>0) {
    start_play++;
  }

  //playing phase
  char miss_c;
  char miss_r;
	int turn = 1; // player 1 - 1; player 2 - 2
	
	char bufferCoor[2];
	
	while (!game_over(home, opponent)) {
		display(home, opponent);
		if (turn % 2 == player_num % 2) {
			while(!parse_missile(&miss_c, &miss_r, home, opponent)) {	
			}
		  if (player_num == 1) {
		    write(client_socket, bufferCoor, sizeof(bufferCoor));
		  } else {
		    write(server_socket, bufferCoor, sizeof(bufferCoor));
		  }
			place_missile(miss_c, miss_r, opponent);
		}
		turn++;
	}

	
	/*
  //while (!game_over(home, opponent) && start_play) {
  while (1) {
    display(home, opponent);
    while(!parse_missile(&miss_c, &miss_r, home, opponent)){
    }
    place_missile(miss_c, miss_r, opponent);
  }
	*/

  //game over
  if (game_over(home, opponent) == 1) {
    printf("\nGAME OVER. You've lost.\n");
  }
  else if (game_over(home, opponent) == 2) {
    printf("\nCONGRATULATIONS! You've won!\n");
  }
  close(client_socket);
  //close(listen_socket);
  //close(server_socket);

  return 0;
}
