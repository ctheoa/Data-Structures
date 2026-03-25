#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

class tree
{
  private:
  Node *root;//κόμβος ρίζα
  int *arr;//πίνακας όπου αποθηκεύουμε αρχικά τα στοιχεια για να τα βάλουμε στη συνέχεια στο δέντρο
  int size;//ο αριθμός των κόμβων του δέντρου

  public:
  tree();
  
  void Build(string str);//κατασκευάζεται το δεντρο
  int Getsize();//γυρνάει τον αριθμό των αριθμό των κόμβων του δέντρου
  void addsize();
  void msize();
  string search(int key);//ψάχνει τον κόμβο με όνομα key
  Node *Findmin(Node *n);// όπου n δίνουμε τη ρίζα του δέντρου για να βρεί το ελάχιστο στοιχείο
  Node* Insert(Node *n, int numb);//προσθήκη κόμβου
  Node *Delete(Node *n,int numb);//διαγραφή κόμβου
  Node *leftrotate(Node *n);//αριστερή περιστροφή
  Node *rightrotate(Node *n);//δεξιά περιστορφή 

  
  Node *lrrotate(Node *parent);//αριστερή και δεξία περιστροφή
  Node *rlrotate(Node *parent);//δεξιά και αριστερή περιστροφή
  Node *getroot();//επιστρέφει τη ρίζα
  void Setroot(Node *root);//αλλάζει τη ρίζα
  int maximum(int a,int b);//παίρνει δυο ακέραιους και αποφασίζει ποιός είναι μεγαλύτερος.Θα χρειαστεί στα ύψη όπου η συνθήκη θα ήταν μεγάλη χωρις αυτή την συνάρτηση
  int Calc_h(Node *n);//υπολογισμός ύψους
  int diafora(Node *parent);//με βαση τα ύψη των δύο υποδέντρων 
  Node *Calc_bf(Node *parent);//αλλάζει τη ισορροπια ενός κόμβου με βάση τις περιστροφές
  void printInorder(Node* node);//για λόγους επαλύθευσης
};
#endif