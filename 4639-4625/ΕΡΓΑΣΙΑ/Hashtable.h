#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "Nodeht.h"
using namespace std;

class Hashtable{
private:
  int size;  //πλήθος στοιχείων
  Nodeht **ar;  //πίνακας αποθήκεθσης στοιχείων
  int htsize;  //μέγεθος HashTable
public:
  Hashtable();  //Κατασκευαστής
 // ~Hashtable();  //Καταστροφέας
  void Build(string str);
  int GetSize();  //επιστρέφει πλήθος στοιχείων
  void Insert(int num);  //εισάγει στοιχεία στον πίνακα
  string Search(int num);  //επσιτρέφει SUCCES ή FAILURE αν υπαρχει ο αριθμός num ή οχι αναλόγως
  void HandleOverload();
};

#endif