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

RecordSet init(int size) {
  if (size == 0) return {nullptr, 0};
  RecordSet rs = {new Record[size], size};
  for (int idx = 0; idx < rs.size; idx++) {
    rs.records[idx].name = nullptr;
    rs.records[idx].grade = -2;
  }
  return rs;
}

void drop(RecordSet& rs) {
  for (int idx = 0; idx < rs.size; idx++) {
    delete[] rs.records[idx].name;
  }
  delete[] rs.records;
  rs.records = nullptr;
  rs.size = 0;
}

int insert(RecordSet& rs, const char* name, int grade) {
  for (int idx = 0; idx < rs.size; idx++) {
    if (rs.records[idx].name == nullptr) {
      rs.records[idx].name = new char[strlen(name) + 1];
      strcpy(rs.records[idx].name, name);
      rs.records[idx].grade = grade;
      return idx;
    }
  }
  return -1;
}

int search(const RecordSet& rs, const char* name) {
  for (int idx = 0; idx < rs.size; idx++) {
    if (rs.records[idx].name == nullptr) continue;
    if (strcmp(rs.records[idx].name, name) == 0) return idx;
  }
  return -1;
}

int update(RecordSet& rs, const char* name, int grade) {
  int pos = search(rs, name);
  if (pos == -1) return -1;
  rs.records[pos].grade = grade;
  return pos;
}

int remove(RecordSet& rs, const char* name) {
  int pos = search(rs, name);
  if (pos == -1) return -1;
  delete[] rs.records[pos].name;
  rs.records[pos].name = nullptr;
  rs.records[pos].grade = -2;
  return pos;
}

RecordSet load(const char* filename) {
  ifstream fs(filename);
  if (!fs) return init(0);
  int num;
  fs >> num;
  RecordSet rs = init(num);
  char buf[256];
  int grade;
  for (int idx = 0; idx < rs.size; idx++) {
    fs >> buf >> grade;
    if (strcmp(buf, "CANCELLATO") == 0) {
      rs.records[idx].name = 0;
      rs.records[idx].grade = -2;
    } else {
      rs.records[idx].name = new char[strlen(buf) + 1];
      strcpy(rs.records[idx].name, buf);
      rs.records[idx].grade = grade;
    }
  }
  return rs;
}

int save(const RecordSet& rs, const char* filename) {
  ofstream fs(filename);
  if (!fs) return -1;
  fs << rs.size << endl;
  for (int idx = 0; idx < rs.size; idx++) {
    fs << (rs.records[idx].name ? rs.records[idx].name : "CANCELLATO") << " "
       << rs.records[idx].grade << endl;
  }
  return 0;
}

#ifndef __TESTS__

int main() {
  // da usare per i vostri tests
  return 0;
}

#endif
