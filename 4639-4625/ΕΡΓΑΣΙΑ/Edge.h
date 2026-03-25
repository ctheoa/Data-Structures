#ifndef EDGE_H
#define EDGE_H
#include "Node.h"
class  Node;
class Edge
{
private:
  int w;//βάρος ακμής
  Node *v;//τελικός κόμβος
  int src;//αρχικός κόμβος όμως χρησιμοποιείται μόνο στον αλγόριθμο του kruskal
public:
  Edge();
  Edge(Node *v,int w,int src);//Constructor 
  int Getw();//Getter βαρος
  void Setw(int w);//Setter βαρος
  Node *Getv();//Getter τελικός κόμβος
  void Setv(Node *v);//Setter τελικός κόμβος
  int Getsrc();//Getter αρχικός κόμβος
  void Setsrc(int src);//Setter αρχικός κόμβος

};
#endif