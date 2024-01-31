// HEADERS ---------------------------------------------------------------------
#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

// STRUTTURE DATI --------------------------------------------------------------
struct Record { // dichiara una struct che contiene un puntatore e una variable int
  char* name; 
  int grade;
};

struct RecordSet { // dichiara una struct che contiene un puntatore di record (quindi puntatore di puntatore e int ) e una variable int
  Record* records;
  int size;
};

// FUNZIONI --------------------------------------------------------------------

RecordSet init(int size) {
  if (size == 0) return {nullptr, 0}; // se la dimensione è 0 restituisce il nullptr (come un puntatore null) e 0 (dimensione 0)
  RecordSet rs = {new Record[size], size}; // alloca il puntatore esterno e la variabile size
  for (int idx = 0; idx < rs.size; idx++) { // scorre il puntatore esterno appena allocato
    rs.records[idx].name = nullptr; // inizializza tutti i puntatori interni a null (non è un'allocazione)
    rs.records[idx].grade = -2; // setta il punteggio a -2
  }
  return rs;
}

void drop(RecordSet& rs) {
  for (int idx = 0; idx < rs.size; idx++) { // essendo un puntatore che contiene altri puntatori, scorre il puntatore esterno 
    delete[] rs.records[idx].name;  // e dealloca prima i puntatori interni
  }
  delete[] rs.records; // poi dealloca il puntatore esterno
  rs.records = nullptr; // setta a null il puntatore esterno
  rs.size = 0; // azzera la dimensione
}

int insert(RecordSet& rs, const char* name, int grade) {
  for (int idx = 0; idx < rs.size; idx++) { // scorre il puntatore esterno
    if (rs.records[idx].name == nullptr) { // controlla se il puntatore interno nella posizione idx è null (quindi non allocato)
      rs.records[idx].name = new char[strlen(name) + 1]; // alloca il puntatore è gli dà la dimensione del nome + 1 (per il terminatore stringa)
      strcpy(rs.records[idx].name, name); // copia il nome nel puntatore appena allocato
      rs.records[idx].grade = grade; // assegna il punteggio dello studente(persona)
      return idx; // restituisce la posizone del puntatore interno nel puntatore esterno
    }
  }
  return -1; 
}

int search(const RecordSet& rs, const char* name) {
  for (int idx = 0; idx < rs.size; idx++) { // scorre il puntatore esterno
    if (rs.records[idx].name == nullptr) continue; // se il puntatore interno in posizione idx non è allocato salta alla prossima posizone (cioè idx++)
    // è "continue" che fa il salto
    if (strcmp(rs.records[idx].name, name) == 0) return idx; // se il valore del punatore interno in posizione idx è uguale al nome restituisce la  posizone del puntatore interno nel puntatore esterno 
    // strcmp(x, y) confronta tutti i caratteri delle 2 variabili "x, y" posizione per posizione, se sono uguali restituisce 0 altrimenti restituisce un altro numero
  }
  return -1; 
}

int update(RecordSet& rs, const char* name, int grade) {
  int pos = search(rs, name); // ricava la posizione del nome dato usando la funzione search
  if (pos == -1) return -1;
  rs.records[pos].grade = grade; // aggiorna il punteggio dello studente(persona) se esiste
  return pos;
}

int remove(RecordSet& rs, const char* name) {
  int pos = search(rs, name);
  if (pos == -1) return -1;
  delete[] rs.records[pos].name;  // dealloca il puntatore interno in posizione pos
  rs.records[pos].name = nullptr; // lo setta a null
  rs.records[pos].grade = -2; // setta il punteggio a -2
  return pos;
}

RecordSet load(const char* filename) {
  ifstream fs(filename); // legge in input il file nel percorso specificato in filename
  if (!fs) return init(0); // se non trovo il file o percorso specificato restituisce il valore della funzione init
  int num;
  fs >> num; // mette il valore della prima riga in num
  RecordSet rs = init(num); // num essendo la dimensione del punatore esterno lo usa per inizializzare le struct
  char buf[256]; // dichiara char con dimensione fissa (256)
  int grade;
  for (int idx = 0; idx < rs.size; idx++) { // scorre dimensione volte
    fs >> buf >> grade; // partendo dalla seconda riga del file mette il valore prima di uno spazio in buf e il valore dopo lo spazio in grade
    if (strcmp(buf, "CANCELLATO") == 0) { // se il nome è uguale a cancellato
      rs.records[idx].name = 0; // setta il nome a 0 (qui è meglio settalo a nullptr)
      rs.records[idx].grade = -2; // setta il punteggio a -2
    } else { // altrimenti fa la stessa cosa che fa nella funzione insert
      rs.records[idx].name = new char[strlen(buf) + 1];
      strcpy(rs.records[idx].name, buf);
      rs.records[idx].grade = grade;
    }
  }
  return rs;
}

int save(const RecordSet& rs, const char* filename) {
  ofstream fs(filename); // legge in output il file nel percorso specificato in filename
  // essendo in output se il percorso è giusto ma il file non esiste lo crea direttamente senza andare il errore
  if (!fs) return -1; // se il percorso è sbagliato va in errore e restituisce -1
  fs << rs.size << endl; // scrive la dimensione del puntatore esterno nella prima riga endl gli dice di andare alla riga successiva
  for (int idx = 0; idx < rs.size; idx++) { // scorre il puntatore esterno
    // a partire dalla seconda riga se il puntatore interno è allocato mette il nome poi lo spazio e il punteggio altrimenti mette cancellato poi lo spazio e il punteggio
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
