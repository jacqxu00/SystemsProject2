#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int player(int argc, char ** argv){
  /*PARAMETERS player 1 should run with cmd line arg "1"
    player 2 should run with cmd line arg "2" and player 1's IP address
  */
  /*RETURNS 1 for player 1 ("server")
    2 for player 2 ("client")
    0 for error
  */
  if(argc >= 2){
    if(!strcmp(argv[1], "1")){
      return 1;
    }else if(!strcmp(argv[1], "2")){
      if(argc >= 3){
	//check for valid IP address?
	return 2;
      }else{
	printf("specify player 1's IP address");
	exit(1);
      }
    }
  }else{
    printf("insufficient arguments");
    exit(1);
  }

  return 0;
}

int connect(int player, int address){ //return if successfully connected

  return 1;
  return 0;
}
