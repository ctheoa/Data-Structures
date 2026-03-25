#ifndef MINHEAP_H
#define MINHEAP_H
#include <string>
#include <iostream>
using namespace std;

class MinHeap{
private: 
  int size; //Μέγεθος Σωρού
  int capacity;  //Χωρητικότητα Σωρού
  int *arr;  //Πίνακας των στοιχείων του Σωρού
  int parent(int i); //επιστρέφει την θέση του γονέα του στοιχείου που βρίσκεται στην θέση i
  int leftchild(int i);//επιστρέφει την θέση του αριστερού παιδιού του στοιχείου που βρίσκεται στην θέση i
  int rightchild(int i);//επιστρέφει την θέση του δεξιού παιδιού του στοιχείου που βρίσκεται στην θέση i
public:
   MinHeap();  //Κατασκευαστής MinHeap
   ~MinHeap();    //Καταστροφέας MinHeap
   void Build(string str);  //Περνάει τα στοιχεία του σωρού στον πίνακα
   void MinHeapify(int i);  //Δίνει μορφή MinHeap στο υποδένδρο με κορυφή το στοιχείο της θέσης i
   int GetSize();  //Επιστρέφει το μέγεθος του MinHeap
   int GetMin();  //Επιστρέφει το μικρότερο στοιχείο του MinHeap

   void Insert(int a);  //Εισάγει το στοιχείο a στο MinHeap
   void DeleteMin();  //Διαγράφει το ελάχιστο στοιχείο του MinHeap

   void HandleOverload();  //Μεγαλώνει τον πίνακα σε περίπτωση που δεν φτάνει η χωρητικότητα
   void swap(int& a, int& b);  //αλλάζει τα a και b
};

#endif