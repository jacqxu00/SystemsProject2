#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//ship structs
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

//function headers
