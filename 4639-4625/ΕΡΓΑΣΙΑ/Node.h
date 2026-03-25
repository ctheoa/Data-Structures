#ifndef NODE_H
#define NODE_H
#include "Edge.h"
class Edge;
class Node
{
  private:
  Node *l;//Αριστερό παιδί κόμβος
  Node *r;//Δεξι παιδί κόμβος
  int numb;//όνομα-αριθμός κόμβου 
  public:
  bool visited;//αν έχει επισκεφτεί
  Edge *e;//πίνακας ακμών με άλλους κόμβους δηλάδη οι γειτονές του
  int ecount;//το πλήθος των γειτώνων
  int dist;//Για τον αλγόριθμο του Dijkstra
  Node();
  Node(int num);//Constructor για τον κόμβο
  int Getnumb();//Getters και Setters:
  void Setnumb(int num);
  Node *Getl();
  void Setl(Node *l);
  Node *Getr();
  void Setr(Node *r);
  Edge Gete(int k);
  void Sete(int k);
   
  
};
#endif