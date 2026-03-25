#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <iostream>
#include "Node.h"
#include "Edge.h"
using namespace std;

class Graph{
private:
 Node **g;//δυναμικός πίνακας κόμβων
 int size;//πλήθος κόμβων
  int capacity=1000;//αρχική χωριτικότητα κόμβων στον g 
public:
  Graph();
  void Build(string file);//Συνάρτηση για το διάβασμα ακμών απο το αρχείο
  void Insert(int a,int b,int w);//Προσθήκη ακμής
  void Delete(int a,int b,bool* non);//Διαγραφή ακμής
  int *GetSize();//επιστρέφει το πλήθος των κόμβων και των ακμών
  int min_geitonas(int thesi1);//Βοηθητική συνάρτηση για τον αλγόριθμο του Dikjstra για τον ελάχιστο γειτον του κόμβου κάθε φορά
  int shortest_path(int arxi,int telos);//Αλγόριθμος του Dikjstra
  //int Getweight(int arxi,int telos);//Getter Βαρους
  int min_span_tree();//Αλγόριθμος Kruskal
  void DFS(int v);//Depth first search
  int CCC();//Connected Components(συνυστώσες)
  int find_parent(int parent[],int i);//βοηθητική συνάρτηση για τον αλγόριθμο του Kruskal
  //int find_node_index(int num);//η θέση ενός κόμβου με την τιμή num στον πινακα g
  void union_parent(int parent[],int x, int y);//βοηθητική συνάρτηση Kruskal
  void quicksort(Edge *arr,int low,int high);//QCSORT MIN
  int partition(Edge *arr,int low,int high,int pivot);//QCSORT για το pivot
  bool check(int i,int j,Edge *edges,int totalEdges);//Αν συμπεριλαμβάναμε ηδη τον κόμβο στον ελάχιστο δέντρο
};


#endif