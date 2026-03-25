#ifndef MAXHEAP_H
#define MAXHEAP_H
#include <string>
#include <iostream>
using namespace std;

class MaxHeap{
private: 
  int size;  //Μέγεθος Σωρού
  int capacity;  //Χωρητικότητα Σωρού
  int *arr;  //Πίνακας των στοιχείων τοθ Σωρού
  int parent(int i);  //επιστρέφει την θέση του γονέα του στοιχείου που βρίσκεται στην θέση i
  int leftchild(int i);  //επιστρέφει την θέση του αριστερού παιδιού του στοιχείου που βρίσκεται στην θέση i
  int rightchild(int i);  //επιστρέφει την θέση του δεξιού παιδιού του στοιχείου που βρίσκεται στην θέση i
public:
   MaxHeap();    //Κατασκευαστής ΜaxHeap
 //  ~MaxHeap();  //Καταστροφέας MaxHeap
   void Build(string str);
   void MaxHeapify(int i);  //Δίνει μορφή MinHeap στο υποδένδρο με κορυφή το στοιχείο της θέσης i
   int GetSize();  //Επιστρέφει το μέγεθος του MaxHeap
   int GetMax();  //Επιστρέφει το μεγαλύτερο στοιχείο του MaxHeap

   void Insert(int a);  //Εισάγει το στοιχείο α στο MaxHeap
   void DeleteMax();  //Διαγράφει το μεγιστο στοιχείο του MaxHeap

   void HandleOverload();  //Μεγαλώνει τον πίνακα σε περίπτωση που δεν φτάνει η χωρητικότητα
   void swap(int& a, int& b);  //αλλάζει τα a και b
  void SetSize(int size);  //Αλλαγή μέγεθος
};

#endif