// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct GameWorld {
  int* cells;
  int rows;
  int columns;
};

// FUNZIONI --------------------------------------------------------------------

GameWorld init(int n, int m, int* cells) { return {nullptr, 0, 0}; }

void drop(GameWorld& gw) {}

int get(const GameWorld& gw, int i, int j) { return -1; }

void set(GameWorld& gw, int i, int j, int value) {}

int count(GameWorld& gw, int i, int j) { return -1; }

GameWorld copy(const GameWorld& gw) { return init(0, 0, nullptr); }

void step(GameWorld& gw) {}

GameWorld load(const char* filename) { return init(0, 0, nullptr); }

int save(const GameWorld& gw, const char* filename) { return 0; }

void print(const GameWorld& gw) {
  printf("GameWorld %d x %d\n", gw.rows, gw.columns);
  for (int i = 0; i < gw.rows; i++) {
    for (int j = 0; j < gw.columns; j++) {
      printf("%d ", get(gw, i, j));
    }
    printf("\n");
  }
  printf("\n");
}

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
