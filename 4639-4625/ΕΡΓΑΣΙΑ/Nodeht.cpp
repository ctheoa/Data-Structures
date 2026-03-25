#include "Nodeht.h"

Nodeht::Nodeht(int a){
  value=a;  //θέτω ως τιμή τον a
  next=nullptr;  //και αρχικοποιώ στον nullptr τον επόμενο κόμβο
}

void Nodeht::SetNext(Nodeht *next){
  this->next=next;  //βάζω ως επόμενο κόμβο τον next
}

Nodeht* Nodeht::GetNext(){
  return next;  //επιστρέφει τον επόμενο κόμβο
}

int Nodeht::GetValue(){
  return value;  //επιτρέφει την τιμή του κόμβου
}

