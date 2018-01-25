#include "battleship.h"

int listen_socket; //for player 1
int client_socket; //for player 1
int server_socket; //for player 2

static void sighandler (int signo) {
	if (signo == SIGINT) {
		printf("Player has been interrupted.\n");
		close(client_socket);
		close(listen_socket);
		close(server_socket);
		exit(0);
	}
	if (signo == SIGSEGV) {
		printf("Player has been interrupted.\n");
		close(client_socket);
		close(listen_socket);
		close(server_socket);
		exit(0);
	}
}

void pretty_spacing (int x) {
	int i;
	for (i = 0; i < x; i++) {
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
	  	char coord = home->board_[row][c];
		
		if (coord == '.') { printf(WATER ". " RESET); }
		else if (coord == 'H') { printf(HIT "H " RESET); }
		else if (coord == '*') { printf(MISS "* " RESET); }
		else { printf(SHIP "%c " RESET, coord); }
	}
	printf("          ");

	//print opponent board row
	printf("%d ", row);
	int d;
	for (d = 0; d < opp->cols; d++) {
		int coor = opp->board_[row][d];

		if (coor == '.') { printf(WATER ". " RESET); }
		else if (coor == 'H') { printf(HIT "H " RESET); }
		else if (coor == '*') { printf(MISS "* " RESET); }
		else { printf(WATER ". " RESET); }

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

	else if (opp->board_[r][c] == 'H' || opp->board_[r][c] == '*') {
		display(home, opp);
		printf("\nERROR: You've already entered this coordinate, please try again.\n");
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

	if (scanned != 1) {
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

void place_ship (char ship, char col, char row, char dir, struct board * home, char shipP[6][13]) {

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
	//printf("buffer: %s", buffer);

	//printf("scanned int: %d\n", scanned);

	if (scanned != 2){
		display(home, opp);
		printf("\nERROR: coordinate invalid, please try again. \n");
		return 0;
	}

	return missile_valid(*col_p, *row_p, home, opp);
}

void place_missile (char col, char row, struct board * opp, int attacking, char * string) {
	int c = col - 'A';
	int r = row - '0';

	if (opp->board_[r][c] == '.') {
		opp->board_[r][c] = '*';
		if (attacking) {
		        sprintf(string, "You've missed. It is now your opponent's turn.\n");
		}
		else {
		        sprintf(string, "Your opponent has missed. It is now your turn.\n");
		}
	}

	else {
		char current = opp->board_[r][c];
		opp->board_[r][c] = 'H';
		char * shipname = "";
		int shipsize = 0;

		if (current == 'A') {
			shipname = "Aircraft";
			shipsize = 5;
		} else if (current == 'B') {
			shipname = "Battleship";
			shipsize = 4;
		} else if (current == 'C') {
			shipname = "Cruiser";
			shipsize = 3;
		} else if (current == 'D') {
			shipname = "Destroyer";
			shipsize = 2;
		} else if (current == 'S') {
			shipname = "Submarine";
			shipsize = 3;
		}

		if (attacking) {
			sprintf(string, "You've hit your opponent's %s (size %d)! It is now your\nopponent's turn.\n", shipname, shipsize);
		}
		else {
			sprintf(string, "Your %s's been hit! It is now your turn.\n", shipname);
		}
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
	signal(SIGINT, sighandler);
	signal(SIGSEGV, sighandler);

	//network setup
	int player_num;
	//int listen_socket; //for player 1
	//int client_socket; //for player 1
	//int server_socket; //for player 2
	char * address = argv[2];
	printf("%s", address);

	player_num = player(argc, argv);
	connecting(player_num, address, &listen_socket, &client_socket, &server_socket);

	printf("\e[8;25;68;t");

	//instructions
	int start_setup = 0;
	char buffer1[256];
	char buffer2[256];

	pretty_spacing(30);
	printf(WELCOME_MSG);
	fgets(buffer1, sizeof(buffer1), stdin);

	if (sizeof(buffer1) > 0) {
		pretty_spacing(30);
		printf(SETUP_INSTRUCTIONS);
		fgets(buffer2, sizeof(buffer2), stdin);
	}

	if (sizeof(buffer2) > 0) {
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

	while (ships_placed < 5 && start_setup) {
		display(home, opponent);
		while(!parse_ship(&ship, &col, &row, &dir, home, opponent, shipPlace)){}
		place_ship(ship, col, row, dir, home, shipPlace);
		ships_placed++;
	}

	display(home, opponent);
	printf("\n\n\nWaiting for other player to finish placing ships...\n");

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
	}
	else {
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
	int turn = 1;
	char displayString[256];

	char bufferCoor[2];

	while (!game_over(home, opponent) && start_play) {
		display(home, opponent);
		printf("\n\n");
		printf(displayString);
		if (turn % 2 == player_num % 2) {
			printf("\nYour turn, player %d\n", player_num);
			while(!parse_missile(&miss_c, &miss_r, home, opponent)) {}
			bufferCoor[0] = miss_c;
			bufferCoor[1] = miss_r;
			if (player_num == 1) {
				write(client_socket, bufferCoor, sizeof(bufferCoor));
			}
			else {
				write(server_socket, bufferCoor, sizeof(bufferCoor));
			}
			//printf("%d turn ended\n", turn);
			place_missile(miss_c, miss_r, opponent, 1, &displayString);
			//turn++;
		}
		else {
			//read
			printf("\nWaiting for the other player...\n");
			if (player_num == 1) {
				read(client_socket, bufferCoor, sizeof(bufferCoor));
			} else {
				read(server_socket, bufferCoor, sizeof(bufferCoor));
			}
			//parse bufferCoor into miss_c & miss_r
			//printf("after reading\n");
			//printf("bufferCoor: %s\n", bufferCoor);
			miss_c = bufferCoor[0];
			miss_r = bufferCoor[1];
			//printf("miss_c: %c \tmiss_r: %c\n", miss_c, miss_r);
			place_missile(miss_c, miss_r, home, 0, &displayString);
			//printf("%d turn ended\n", turn);
		}
		turn++;
	}

	//game over
	if (game_over(home, opponent) == 1) {
		printf("\nGAME OVER. You've lost.\n");
	}
	else if (game_over(home, opponent) == 2) {
		printf("\nCONGRATULATIONS! You've won!\n");
	}

	close(client_socket);
	close(listen_socket);
	close(server_socket);

	return 0;
}
