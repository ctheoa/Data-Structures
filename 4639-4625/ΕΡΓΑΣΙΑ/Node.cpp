#include "Node.h"
#include <iostream>
#include "Edge.h"
using namespace std;
//Υλοποίηση του .h αρχείου
Node :: Node(){}
Node :: Node(int num)
{
  l = nullptr;
  r = nullptr;
  numb=num;
  e = new Edge[1000];
  ecount = 0;
}
int Node::Getnumb(){
  return numb;}
void Node::Setnumb(int num){numb=num;}

Node *Node::Getl(){return l;}
void Node::Setl(Node *l){this->l=l;}

Node *Node::Getr(){return r;}
void Node::Setr(Node *r){this->r=r;}





