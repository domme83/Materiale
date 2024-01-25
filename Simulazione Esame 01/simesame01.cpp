// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  char name[128];
  int value;
};

struct RecordSet {
  Record* records;
  int size;
  int capacity;
};

// FUNZIONI --------------------------------------------------------------------

RecordSet init() { return {nullptr, 0, 0}; }

void drop(RecordSet& rs) {}

int insert(RecordSet& rs, const char* name, int value) { return -2; }

int search(RecordSet& rs, const char* name) { return -2; }

int remove(RecordSet& rs, const char* name) { return -2; }

int update(RecordSet& rs, const char* name, int value) { return -2; }

int load(RecordSet& rs, const char* filename) { return -2; }

int save(RecordSet& rs, const char* filename) { return -2; }

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
