#include "MinHeap.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


int MinHeap::parent(int i){
  return (i-1)/2;   //θέση γονέα του στοιχείου που βρίσκεται στην θέση i
}
int MinHeap::leftchild(int i){
  return 2*i+1;     //θέση αριστερού παιδιού του στοιχείου που βρίσκεται στην θέση i
}
int MinHeap::rightchild(int i){
  return 2*i+2;     //θέση δεξιού παιδιού του στοιχείου που βρίσκεται στην θέση i
}

MinHeap::MinHeap(){
  
}

void MinHeap::HandleOverload(){
  int m=capacity;
    capacity*=2;  //διπλασιάζω την χωρhτικότητα
      int *temp=new int[capacity];  //φτιχνω έναν προσωρινο πίνακα που αποθηκεύω τα στοιχεία του arr
        for(int j=0;j<m;j++)
          temp[j]=arr[j];
      delete[] arr;    //διαγράφω τον arr 
    arr=temp;   //και του περνάω τα στοιχεία που είχε πριν 
}

void MinHeap::Build(string str){
  ifstream infile;
  infile.open(str);  //ανοίγω το αρχείο

  int a,i=0;
  capacity=1000;  //αρχικοποιώ την χωρητικότητα στο 1000
  size=0;
//SetSize(0);  //αρχικοποιώ το size σε 
  arr=new int [1000];  //αρχικοποιώ τον πίνακα στις 1000 θέσεις

  while(infile>>a){  //όσο διβάζει ακεραίους
    if(i>=capacity)  //ελέγχει αν ο χώρος επαρκεί για να προστεθεί ο a
      HandleOverload();   //αν δεν επαρκεί καλεί την HandleOverload

  arr[i]=a;  //αν επαρκεί η χωρητικότητα περνάω το a στον πίνακα
  i++;  
  }
  
  infile.close();   //κλείνει το αρχείο 
  
  size=i;  //το μέγεθος ειναι οσο και το i
    //Αρχίζω και δίνω μορφή minheap από το τελευταίο υποδένδρο μέχρι και το ολόκληρο
    for(int j=size/2-1;j>=0;j--)
      MinHeapify(j);
}

void MinHeap::MinHeapify(int i){
    int min=i;    
    if(leftchild(i)<size&&arr[min]>arr[leftchild(i)])
      min=leftchild(i);
    if(rightchild(i)<size&&arr[min]>arr[rightchild(i)])
      min=rightchild(i);
  //Βρίσκω την θέση του ελαχιστου στοιχείου μεταξύ του στοιχείου στην θέση i και των παιδιών του
    if(min!=i){
      swap(arr[min],arr[i]);
      MinHeapify(min);  
    }
  //Αν το ελάχιστο στοιχείο είναι ένα απο τα παιδιά του τότε το αντικαθιστώ με αυτό και του δίνω μορφή MinHeap στο υποδένδρο με κορυφή το ελάχιστο 
  
}

MinHeap::~MinHeap() {
   // delete[] arr;   //Διαγράφω τον arr
}

int MinHeap::GetSize(){
  return size;  //επιστρέφει το μέγεθος του σωρού
}

int MinHeap::GetMin(){
  return arr[0];   //επιστρέφει το ελάχιστο στοιχείο το οποίο λόγο minheap  είναι στην κορυφή
}

void MinHeap::Insert(int a){
  if(size>=capacity)  //ελέγχω αν υπάχει χώρος για να προσθέσω το a
    HandleOverload();   //αν δεν υπάχει καλώ την HandleOverload
     
    arr[size]=a;  //αν υπάρχει βάζω το a στην πρώτη διαθέσιμη θέση του πίνακα 
    int j=size;   
    size++;   //αυξάνω το μέγεθος κατα ενα με την προσθήκη του a
   
    while(arr[j]<arr[parent(j)]&&j!=0){   //όσο το στοιχείο είναι μεγαλύτερο απο τον γονείο του και το στοιχείο δεν εχει φτάσει στην ρίζα
      swap(arr[j],arr[parent(j)]);  //το ανταλλάσω με τον γονέα
      j=parent(j);  //βάζω και τον δείκτη να δείχνει στον δείκτη του γονέα
    }
}

void MinHeap::DeleteMin(){
  arr[0]=arr[size-1];   //βάζω το τελευταίο στοιχείο του σωρού στην ρίζα

  size--;      //μειώνω το μέγεθοσ κατα ένα αφού διέγρψα το ελάχιστο στοιχείο
  MinHeapify(0);     //και επαναφέρω την μορφή του MinHeap
}

void MinHeap::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

//*******ΣΚΟΥΠΙΔΙΑ************\\ΟΧΙ ΣΒΗΣΙΜΟ ΟΜΩΣ
/*
void MinHeap::PrintHeap(){
  for(int i=0;i<GetSize();i++)
    cout<<arr[i]<<" ";
}

//ΣΒΗΜΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ
//capacity*=2;
//  int *temp=new int[capacity];
//    for(int j=0;j<size;j++)
//      temp[j]=arr[j];
//  delete[] arr;
//arr=temp;
  while(leftchild(j)<size||rightchild(j)<size){  
  if(arr[leftchild(j)]>arr[rightchild(j)]){
    int temp=arr[j];
    arr[j]=arr[rightchild(j)];
    arr[leftchild(j)]=temp;
    j=rightchild(j);
  }else{
    int temp=arr[j];
    arr[j]=arr[leftchild(j)];
    arr[leftchild(j)]=temp;
    j=leftchild(j);
  }
}*/

