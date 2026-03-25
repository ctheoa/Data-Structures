#include "Hashtable.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;



Hashtable::Hashtable(){
  
}
/*
Hashtable::~Hashtable(){
  for(int i=0;i<htsize;i++){    //για κάθε θέση του hashtable 
    Nodeht* N=ar[i];  
    while(N){  //όσο υπάρχει επόμενος κόμβος στην ίδια αλυσίδα
      Nodeht* temp=N;  //τον περνάει στο temp
      N=N->GetNext();  //βάζει τον επόμενό του στην N
      delete temp;  //και διαγράφει τον τωρινό
    }

  }
  delete[] ar;  //τέλος διαγράφω όλο τον πίνακα
}
*/

void Hashtable::HandleOverload(){

  int new_htsize=htsize*2;  //διπλασιάζω το μέγεθος του Hashtable
  Nodeht** temp=new Nodeht*[new_htsize]; //φτιάχνω έναν προσωρινώ πίνακαμε διπλάσιο μέγεθος απο τον προηγοούμενο
  for(int i=0;i<new_htsize;i++)
    temp[i]=nullptr;  //αρχικοποιώ όλες τις θέσεις του με nullptr
  for(int i=0;i<htsize;i++){
    Nodeht *cur=ar[i];  //πέρνω τον πρώτο κόμβο της διεύθυνσης i και τον βάζω στον cur
    while(cur){  //όσο ο cur έχει κόμβο
      Nodeht* next=cur->GetNext();  //περνάω στον next τον επόμενό του
      int index=cur->GetValue()%new_htsize;  
      cur->SetNext(temp[index]); //βάζω ως επόμενο του cur τον temp
      temp[index]=cur;  //περνάω τον cur στη θέση του temp που αντιστοιχεί 
      cur=next;  //και αντικαθιστώ τον cur με τον επόμενω κόμβο στην αλυσίδα
    }
  }
  delete[] ar;  //διαγράφω τον προηγούμενο πίνακα
  ar=temp;  //βάζω τον ar να δείχνει στον temp
  htsize=new_htsize;  //και ενημερώνω το μέγεθος του hashtable
}

void Hashtable::Insert(int num){
  if(size>=htsize/2)
    HandleOverload();
  Nodeht* N=new Nodeht(num);
  if(ar[num%htsize]==nullptr)  //αν δεν υπάρχει κανείς κόμβος σε αυτή την θέση του πίνακα
    ar[num%htsize]=N;  //τότε περνάω τον κόμβο με τον αριθμό a
  else{
    Nodeht* cur=ar[num%htsize];
    while(cur->GetNext())  //όσο υπάρχει επόμενος κόμβος
      cur=cur->GetNext();  //περνάω στον επόμενο
    cur->SetNext(N);  //και όταν δεν υπάρχει πλέον βάζω τον κόμβο με τον αριθμό a
  } 
  size++;  //μεγαλώνω το μέγεθος κατα ένα λόγω εισαγωγής του a
}

void Hashtable::Build(string str){
 
  ifstream infile;  
  infile.open(str);  //ανοίγω το αρχείο που μου δίνεται
  
   htsize=100;   //αρχικοποιώ το μέγεθος του HashTable στα 100
  int a;
  size=0;  //αρχικοποιώ το πλήθος των κόμβων στο 0
  
  ar=new Nodeht*[100];  //δεσμεύω αρχικα 100 θέσεις στον πίνακα
  
  for(int i=0;i<100;i++)  //τις βάζω όλες να δίχνουν nullptr
    ar[i]=nullptr;
  
  while(infile>>a){  //όσο διαβάζει αριθμούς από το αρχείο
    if(size>=htsize/2){  //ελέγχει αν τα στοιχεία έιναι περσσότερα από το μισό μέγεθος του πίνακα
      HandleOverload();  //αν ναι τότε καλεί την HandleOver
    }
    Insert(a);  //αλλιώς εισάγει το στοιχείο στον πίνακα
  }  
  infile.close();  //κλείνω το αρχείο
}

int Hashtable::GetSize(){return size;}  //επιστρέφω πλήθοσ κόμβων



string Hashtable::Search(int a){
  Nodeht* N=ar[a%htsize];
  while(N){  //όσο υπάρχει κόμβος στον δείκτη  του πίνακα που ανήκει το a
    if(N->GetValue()==a)  //αν η τιμή του κόμβου είναι ίση με το a  
      return "SUCCESS";  //επιστρέφει SUCCESS 
  N=N->GetNext();   //εαν όχι περνάει στον επόμενο κόμβο
}
  return "FAILURE";  //και αν τελείωσουν οι κόμβοι πριν βρεθεί το a τότε επιστρέφει FAILURE
}

