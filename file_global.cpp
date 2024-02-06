// ESAME 01
// STRUTTURE DATI --------------------------------------------------------------
struct Record {
  int id;
  char name[128];
  int value;
};

struct RecordSet {
  Record* records;
  int size;
  int capacity;
};

// FUNZIONI DI AIUTO -----------------------------------------------------------

void print(const RecordSet& rs) {
  cout << "RecordSet: " << rs.size << "/" << rs.capacity << endl;
  for (int idx = 0; idx < rs.size; idx++) {
    cout << "  " << rs.records[idx].id << " " << rs.records[idx].name << " "
         << rs.records[idx].value << endl;
  }
}

// FUNZIONI --------------------------------------------------------------------

RecordSet init() {
  // DA IMPLEMENTARE
  RecordSet rs;
  rs.records = nullptr;
  rs.size = 0;
  rs.capacity = 0;
  return rs;
}

void drop(RecordSet& rs) {
  // DA IMPLEMENTARE
  if (rs.records != nullptr) {
    delete[] rs.records;
    rs.records = nullptr;
    rs.size = 0;
    rs.capacity = 0;
  }
}

int search(const RecordSet& rs, int id);
int insert(RecordSet& rs, int id, const char* name, int value) {
  // DA IMPLEMENTARE
  if (search(rs, id) != -1) {
    return -1;
    
  }

  if (rs.records != nullptr) {
    for (int i = 0; i < rs.size; i++) {
      if (rs.records[i].id == -1) {
          rs.records[i].id = id;
          strcpy(rs.records[i].name, name);
          rs.records[i].value = value;
          return i;
      }
    }

  }

  if (rs.size == rs.capacity) {
  	
    Record* tmp = new Record[ (rs.capacity == 0) ? 2 : rs.capacity * 2];
    for (int i = 0; i < rs.size; i++) {
      tmp[i] = rs.records[i];
    }
    delete[] rs.records;
    rs.records = tmp;
    rs.capacity = (rs.capacity == 0) ? 1 : rs.capacity;
    rs.capacity *= 2;
  }
  rs.records[rs.size].id = id;
  strcpy(rs.records[rs.size].name, name);
  rs.records[rs.size].value = value;
  rs.size += 1;
  return rs.size-1;
}

int rcount(const RecordSet& rs) {
  // DA IMPLEMENTARE
  int count = 0;
  for (int i = 0; i < rs.size; i++) {
    if (rs.records[i].id != -1) {
      count += 1;
    }
  }
  return count;
}

int vsum(const RecordSet& rs, const char* name) {
  // DA IMPLEMENTARE
  int sum = 0;
  for (int i = 0; i < rs.size; i++) {
    if (strcmp(rs.records[i].name, name) == 0) {
      sum += rs.records[i].value;
    }
  }
  return sum;
}

int search(const RecordSet& rs, int id) {
  // DA IMPLEMENTARE
  for (int i = 0; i < rs.size; i++) {
    if (rs.records[i].id == id) {
      return i;
    }
  }
  return -1;
}

int find(const RecordSet& rs, const char* name, int start) {
  // DA IMPLEMENTARE
  for (int i = start; i < rs.size; i++) {
    if (strcmp(rs.records[i].name, name) == 0) {

      return i;
    }
  }
  return -1;
}

int update(RecordSet& rs, int id, int value) {
  // DA IMPLEMENTARE
  int pos = search(rs, id);
  if (pos == -1) {
    return -1;
  }
  rs.records[pos].value = value;
  return pos;
}

int remove(RecordSet& rs, int id) {
  // DA IMPLEMENTARE
  int pos = search(rs, id);
  if (pos == -1) {
    return -1;
  }

  rs.records[pos].id = -1;
  strcpy(rs.records[pos].name, " ");
  rs.records[pos].value = 0;

  return pos;
}

int erase(RecordSet& rs, const char* name) {
  // DA IMPLEMENTARE
  int first_pos = -1, pos = -1;
  do {

    pos = find(rs, name, (pos != -1 && (pos + 1) < rs.size ) ? pos + 1 : 0 );
    first_pos = (pos != -1 && first_pos == -1) ? pos : first_pos;
    (pos != -1 ) ? remove(rs, rs.records[pos].id) : 0;

  } while (pos != -1 );

  return first_pos;
}

RecordSet load(const char* filename) {
  // DA IMPLEMENTARE
  ifstream ifs(filename);
  if (!ifs) {
    return init();
  }

  RecordSet rs = init();
  
  while (ifs) {
    if (rs.size == rs.capacity) {
      
      Record* tmp = new Record[ (rs.capacity == 0) ? 2 : rs.capacity * 2];
      if (rs.records != nullptr) {
      for (int i = 0; i < rs.size; i++) {
        tmp[i] = rs.records[i];
      }
      }

      delete[] rs.records;
      rs.records = tmp;
      rs.capacity = (rs.capacity == 0) ? 1 : rs.capacity;
      rs.capacity *= 2;
    }
    ifs >> rs.records[rs.size].id >> rs.records[rs.size].name >> rs.records[rs.size].value;
    rs.size += 1;

  }
  rs.size --;
  return rs;

}

int save(const RecordSet& rs, const char* filename) {
  // DA IMPLEMENTARE
  ofstream ofs(filename);
  if (!ofs) {
    return -1;
  }

  for (int i = 0; i < rs.size; i++) {
    if (rs.records[i].id != -1) {
      ofs << rs.records[i].id << " " << rs.records[i].name << " " << rs.records[i].value << endl;
    }

  }

  return 0;

}


//
//
//
// PROVA 1

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

RecordSet init() {
  RecordSet rs;
  rs.records = nullptr;
  rs.size = 0;
  rs.capacity = 0;
  return rs;
}

void drop(RecordSet& rs) {
  if (rs.records != nullptr) {
    delete[] rs.records;
    rs.records = nullptr;
    rs.size = 0;
    rs.capacity = 0;
  }
}

int search(RecordSet& rs, const char* name);
int insert(RecordSet& rs, const char* name, int value) {
  if (search(rs, name) != -1) {
    return -1;
  }
  if (rs.size == rs.capacity) {
    Record* tmp = new Record[rs.capacity * 2];
    for (int i = 0; i < rs.size; i++) {
      tmp[i] = rs.records[i];
    }
    delete[] rs.records;
    rs.records = tmp;
    rs.capacity *= 2;
  }
  strcpy(rs.records[rs.size].name, name);
  rs.records[rs.size].value = value;
  rs.size += 1;
  return rs.size - 1;
}

int search(RecordSet& rs, const char* name) {
  for (int i = 0; i < rs.size; i++) {
    if (strcmp(rs.records[i].name, name) == 0) {
      return i;
    }
  }
  return -1;
}

int remove(RecordSet& rs, const char* name) {
  int pos = search(rs, name);
  if (pos == -1) {
    return -1;
  }
  for (int i = pos; i < rs.size - 1; i++) {
    rs.records[i] = rs.records[i + 1];
  }
  rs.size--;
  return pos;
}

int update(RecordSet& rs, const char* name, int value) {
  int pos = search(rs, name);
  if (pos == -1) {
    return -1;
  }
  rs.records[pos].value = value;
  return pos;
}

int load(RecordSet& rs, const char* filename) {
  ifstream ifs(filename);
  if (!ifs) {
    return -1;
  }

  drop(rs);
  ifs >> rs.size;
  rs.capacity = rs.size;
  rs.records = new Record[rs.size];

  for (int i = 0; i < rs.size; i++) {
    ifs >> rs.records[i].name >> rs.records[i].value;
  }

  return rs.size;
}

int save(RecordSet& rs, const char* filename) {
  ofstream ofs(filename);
  if (!ofs) {
    return -1;
  }

  ofs << rs.size << endl;
  for (int i = 0; i < rs.size; i++) {
    ofs << rs.records[i].name << " " << rs.records[i].value << endl;
  }

  return rs.size;
}
//------------------FINE CODICE ----------------------------------------------


//PROVA 2

// STRUTTURE DATI --------------------------------------------------------------
struct GameWorld {
  int* cells;
  int rows;
  int columns;
};

// FUNZIONI --------------------------------------------------------------------

int get(const GameWorld& gw, int i, int j) {
  if (i < 0 || i >= gw.rows || j < 0 || j >= gw.columns) return 0;
  return gw.cells[i * gw.columns + j];
}

void set(GameWorld& gw, int i, int j, int value) {
  if (i < 0 || i >= gw.rows || j < 0 || j >= gw.columns) return;
  gw.cells[i * gw.columns + j] = value;
}

int count(GameWorld& gw, int i, int j) {
  int count = 0;
  for (int k = i - 1; k <= i + 1; k++)
    for (int l = j - 1; l <= j + 1; l++)
      if (k != i || l != j) count += get(gw, k, l);
  return count;
}

GameWorld copy(const GameWorld& gw) {
  GameWorld gw2;
  gw2.rows = gw.rows;
  gw2.columns = gw.columns;
  gw2.cells = new int[gw.rows * gw.columns];
  for (int i = 0; i < gw.rows * gw.columns; i++) gw2.cells[i] = gw.cells[i];
  return gw2;
}

GameWorld init(int n, int m, int* cells) {
  GameWorld gw;
  gw.rows = n;
  gw.columns = m;
  gw.cells = new int[n * m];
  if (cells != nullptr) {
    for (int i = 0; i < n * m; i++) gw.cells[i] = cells[i];
  } else {
    for (int i = 0; i < n * m; i++) gw.cells[i] = 0;
  }
  return gw;
}

void drop(GameWorld& gw) {
  delete[] gw.cells;
  gw.cells = nullptr;
  gw.rows = 0;
  gw.columns = 0;
}

int step(GameWorld& gw) {
  GameWorld gw2 = copy(gw);
  int changes = 0;
  for (int i = 0; i < gw.rows; i++) {
    for (int j = 0; j < gw.columns; j++) {
      int c = count(gw, i, j);
      int v = get(gw, i, j);
      if (v == 0 && c == 3) {
        set(gw2, i, j, 1);
        changes++;
      } else if (v == 1 && (c < 2 || c > 3)) {
        set(gw2, i, j, 0);
        changes++;
      }
    }
  }
  drop(gw);
  gw = gw2;
  return changes;
}

GameWorld load(const char* filename) {
  ifstream ifs(filename);
  if (!ifs) return init(0, 0, nullptr);
  int n, m;
  ifs >> n >> m;
  int* cells = new int[n * m];
  for (int i = 0; i < n * m; i++) ifs >> cells[i];
  GameWorld gw = init(n, m, cells);
  delete[] cells;
  return gw;
}

int save(const GameWorld& gw, const char* filename) {
  ofstream ofs(filename);
  if (!ofs) return -1;
  ofs << gw.rows << " " << gw.columns << endl;
  for (int i = 0; i < gw.rows; i++) {
    for (int j = 0; j < gw.columns; j++) {
      ofs << get(gw, i, j) << " ";
    }
    ofs << endl;
  }
  return 0;
}

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

// ----------------------- FINE CODICE -----------------------------------

                                      // PROVA 3

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
