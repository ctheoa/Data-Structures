
#include "Edge.h"
#include "Node.h"
Edge::Edge(){}
Edge::Edge(Node *v,int w,int src)
{
  this->v = v;
  this->w = w;
  this->src = src;
}
Node *Edge::Getv(){return v;}
int Edge::Getw(){return w;}
int Edge::Getsrc(){return src;}
void Edge::Setsrc(int src){this->src =  src;}
void Edge::Setv(Node *v){this->v=v;}
void Edge::Setw(int w){this->w=w;}
