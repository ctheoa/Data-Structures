#include "MaxHeap.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


int MaxHeap::parent(int i){
        return (i-1)/2;  //θέση γονέα του στοιχείου που βρίσκεται στην θέση i
}
int MaxHeap::leftchild(int i){
  return 2*i+1;  //θέση αριστερού παιδιού του στοιχείου που βρίσκεται στην θέση i
}
int MaxHeap::rightchild(int i){
  return 2*i+2;  //θέση δεξιού παιδιού του στοιχείου που βρίσκεται στην θέση i
}

MaxHeap::MaxHeap(){}

void MaxHeap::HandleOverload(){
  int m=capacity;
  capacity*=2;  //διπλασιάζω την χωρhτικότητα
    int *temp=new int[capacity];  //φτιχνω έναν προσωρινο πίνακα που αποθηκεύω τα στοιχεία του arr
      for(int j=0;j<m;j++)
        temp[j]=arr[j];
    delete[] arr;    //διαγράφω τον arr 
  arr=temp;   //και του περνάω τα στοιχεία που είχε πριν 
}


void MaxHeap::Build(string str){
  ifstream infile;
  infile.open(str);   //ανοίγω το αρχείο
  
  int a,i=0;
  capacity=1000;
  size=0;
  
  arr=new int [1000];  //αρχικοποιώ τον πίνακα στις 1000 θέσεις

  while(infile>>a){  //όσο διβάζει ακεραίους
    if(i>=capacity)  //ελέγχει αν ο χώρος επαρκεί για να προστεθεί ο a
     HandleOverload();  //αν δεν υπάχει καλώ την HandleOverload
  
  arr[i]=a;  //αν επαρκεί η χωρητικότητα περνάω το a στον πίνακα
  i++; 
  }
  
  infile.close();  //κλείνει το αρχείο 
  
  size=i;  //το μέγεθος ειναι οσο και το i
  
  for(int j=size/2-1;j>=0;j--)  //Αρχίζω και δίνω μορφή maxheap από το τελευταίο υποδένδρο μέχρι και το ολόκληρο
    MaxHeapify(j);
}


void MaxHeap::MaxHeapify(int i){
  int max=i;
  if(leftchild(i)<size&&arr[max]<arr[leftchild(i)])
    max=leftchild(i);
  if(rightchild(i)<size&&arr[max]<arr[rightchild(i)])
    max=rightchild(i);
  //Βρίσκω την θέση του μεγίστου στοιχείου μεταξύ του στοιχείου στην θέση i και των παιδιών του
  if(max!=i){
    swap(arr[max],arr[i]);
    MaxHeapify(max);  
  }
  //Αν το μεγιστο στοιχείο είναι ένα απο τα παιδιά του τότε το αντικαθιστώ με αυτό και του δίνω μορφή MaxHeap στο υποδένδρο με κορυφή το μέγιστο
}


//MaxHeap::~MaxHeap(){
//    delete[] arr;  //Διαγράφω τον arr
//}

int MaxHeap::GetSize(){
  return size;  //επιστρέφει το μέγεθος του σωρού
}

int MaxHeap::GetMax(){
  return arr[0];  //επιστρέφει το μέγιστο στοιχείο το οποίο λόγο maxheap  είναι στην κορυφή
}

void MaxHeap::Insert(int a){
  if(size>=capacity)  //ελέγχω αν υπάχει χώρος για να προσθέσω το a
   HandleOverload();  //αν δεν υπάχει καλώ την HandleOverload
  
    arr[size]=a;  //αν υπάρχει βάζω το a στην πρώτη διαθέσιμη θέση του πίνακα 
    int j=size;
    size++;  //αυξάνω το μέγεθος κατα ενα με την προσθήκη του a

    while(arr[j]>arr[parent(j)]&&j!=0){  //όσο το στοιχείο είναι μεγαλύτερο απο τον γονείο του και το στοιχείο δεν εχει φτάσει στην ρίζα
      swap(arr[j],arr[parent(j)]);  //το ανταλλάσω με τον γονέα
      j=parent(j);  //βάζω και τον δείκτη να δείχνει στον δείκτη του γονέα
    }
  
}

void MaxHeap::DeleteMax(){
  arr[0]=arr[size-1];  //βάζω το τελευταίο στοιχείο του σωρού στην ρίζα
  
  size--; //μειώνω το μέγεθος κατα ένα αφού διέγρψα το μέγιστο στοιχείο
  MaxHeapify(0);  //και επαναφέρω την μορφή του MaxHeap
}


void MaxHeap::swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

//*******ΣΚΟΥΠΙΔΙΑ************\\ΟΧΙ ΣΒΗΣΙΜΟ ΟΜΩΣ
/*




for(int j=0;j<size;j++)
  cout<<arr[j]<<'\n';

  capacity*=2;
    int *temp=new int[capacity ];
      for(int j=0;j<i;j++)
        temp[j]=arr[j];
    delete[] arr;
  arr=temp;

  
  capacity*=2;
    int *temp=new int[capacity];
      for(int j=0;j<size;j++)
        temp[j]=arr[j];
    delete[] arr;
  arr=temp;

  int tem=arr[parent(j)];
  arr[parent(j)]=arr[j];
  arr[j]=tem;  //το μετακινώ την θέση του γονέα
  j=parent(j);   //βάζω και τον δείκτη να δείχνει στον δείκτη του γονέα
  */