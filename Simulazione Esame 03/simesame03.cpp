// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  char* name;
  int grade;
};

struct RecordSet {
  Record* records;
  int size;
};

// FUNZIONI --------------------------------------------------------------------

RecordSet init(int size) { return {nullptr, 0}; }

void drop(RecordSet& rs) {}

int insert(RecordSet& rs, const char* name, int grade) { return -2; }

int search(const RecordSet& rs, const char* name) { return -2; }

int update(RecordSet& rs, const char* name, int grade) { return -2; }

int remove(RecordSet& rs, const char* name) { return -2; }

RecordSet load(const char* filename) { return {nullptr, 0}; }

int save(const RecordSet& rs, const char* filename) { return -2; }

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
