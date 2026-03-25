#include <iostream>
#include <fstream>
#include <string>
#include <ctime>//για τον χρόνο 
#include "MinHeap.h"
#include "MaxHeap.h"
#include "Graph.h"
#include "Hashtable.h"
#include "tree.h"
#include "Edge.h"

using namespace std;



int main() {

  ifstream myfile;  
  ofstream outfile;
  
  myfile.open("commands.txt");  //ανοίγω το αρχείο με τις εντολές
  outfile.open("output.txt");  //ανοίγω το αρχείο για τα αποτελέσματα
  
   clock_t t;  
  
  int flMIN=0,flMAX=0,flGR=0,flTREE=0,flHASH=0;  //ελέγχουν ανέχει προηγηθεί η εντολή BUILD για κάθε μία δομή
  
  int num=-1,num2=-1,num3=-1;  
  
  string c,d,f;  //c=εντολή,d=δομή,f=αρχείο για τους αριθμούς
  
  while(myfile>>c>>d){  //Οσο διααβάζει εντολή και δομή
      
      if(c=="BUILD")
        myfile>>f;  //Αν είναι BUILD διαβάζει το αρχείο που περιέχει τους αριθμούς
    
      if(c=="INSERT" ||c=="SEARCH"){
        if(d=="GRAPH")
          myfile>>num>>num2>>num3;  //Αν είναι INSERT ή SEARCH για Γράφο δέχεται 3 αριθμούς
        else
          myfile>>num;  //Διαφορετικά έναν αριθμό
      }
      if(c=="DELETE"){
        if(d=="AVLTREE")
          myfile>>num;  //Αν έχουμε DELETE για το AVL διαβάζω έναν αριθμό
        if(d=="GRAPH")
          myfile>>num>>num2;  //Αν είναι για τον Γράφο όμως τότε διαβάζω 2 αριθμούς
      }
    if(c=="COMPUTESHORTESTPATH")
      myfile>>num>>num2;  //Αν η εντολή είναι COMPUTESHORTESTPATH τότε διαβάζω τους 2 κόμβους 

//Σε όλες τις παρακάτω συνθήκες αν διαβαστεί η εντολή BUILD τότε κάνω το flag της εντολής 1.Αν διαβάσει οποιαδήποτε άλλη εντολή δεν εκτελείται αν το flag της δομής δεν είναι 1.
    
  if(d=="MINHEAP "||d=="MINHEAP"){
    t = clock();
     MinHeap Min;
     if(c=="BUILD"){
       Min.Build(f);
       flMIN=1;
     }
      if(flMIN){
      if(c=="GETSIZE")
        outfile<<Min.GetSize()<<'\n'; 
      else if(c=="INSERT")
        Min.Insert(num);
      else if(c=="FINDMIN")
        outfile<<Min.GetMin()<<'\n';
      else if(c=="DELETEMIN")
        Min.DeleteMin();      
      }
      t = clock() - t;
    outfile<<"ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ "<<c<<": "<<(float)t/CLOCKS_PER_SEC<<'\n';
      
    }else if(d=="MAXHEAP "||d=="MAXHEAP"){
      t = clock();
      MaxHeap Max;
    if(c=="BUILD"){
      flMAX=1;
      Max.Build(f);
    }
    if(flMAX){
      if(c=="GETSIZE")
        outfile<<"SIZE: "<<Max.GetSize()<<'\n'; 
      else if(c=="INSERT")
        Max.Insert(num);
      else if(c=="FINDMAX")
        outfile<<"MAX: "<<Max.GetMax()<<'\n';
      else if(c=="DELETEMAX")
        Max.DeleteMax();
    }
    t = clock() - t;
    outfile<<"ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ "<<c<<": "<<(float)t/CLOCKS_PER_SEC<<'\n';
    
    }else if(d=="GRAPH"||d=="GRAPH "){
       Graph Gr;
       t = clock();//αρχίζουμε τον χρόνο
      if(c=="BUILD " || c=="BUILD"){
        Gr.Build(f);//φτιάχνουμε τον γράφο
        flGR=1;
      }
      if(flGR)
      {
        if(c=="COMPUTESHORTESTPATH"){
          outfile<<"Shortest path is : ";
          outfile<<Gr.shortest_path(num, num2)<<"\n";
        }else if (c=="COMPUTESPANNINGTREE"){
          outfile<<"Minimum spanning tree is : ";
          outfile<<Gr.min_span_tree()<<"\n";
        }else if(c=="GETSIZE"){
          outfile<<"Size of graph is : ";
          outfile<<Gr.GetSize()[0]<<" "<<Gr.GetSize()[1]<<"\n";}
        else if(c=="DELETE"){
          bool *non = new bool;
          *non = true;
          Gr.Delete(num,num2,non);
          if (*non == true)
            outfile<<"Edge not found\n";
          else
            outfile<<"Sucecssfully deleted\n";}
        else if(c=="FINDCONNECTEDCOMPONENTS"){
          outfile<<"Number of connected components are: ";
          outfile<<Gr.CCC()<<"\n";}
        else if (c == "INSERT"){
          outfile<<num<<" "<<num2<< " " <<num3<<"\n";
          Gr.Insert(num,num2,num3);
          outfile <<"Ο κόμβος προστέθηκε με επιτυχία\n";
        }
      }
    t = clock() - t;//σταματαμε τον χρόνο 
    outfile<<"ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ "<<c<<": "<<(float)t/CLOCKS_PER_SEC<<'\n';

    
     }else if (d=="AVLTREE"|| d =="AVLTREE ")
  {
    t = clock();//αρχίζουμε τον χρόνο
    static tree T;
    if(c=="BUILD "||c=="BUILD"){
      T.Build(f);
      flTREE=1;
    }
    if(flTREE){
      if(c=="FINDMIN"){
        outfile<<"Minimum value is : ";
        outfile<<T.Findmin(T.getroot())->Getnumb()<<"\n";
      }else if(c=="SEARCH" || c== "SEARCH "){
        string t = T.search(num);
        outfile<<"Search happend with "<<t<<'\n';
      }else if(c=="INSERT"){
        T.addsize();
        T.Setroot(T.Insert(T.getroot(),num));
        outfile<<"Succesfull insertion of number\n";
      }else if(c=="DELETE"){
        if(T.getroot()!= nullptr){
          T.Setroot(T.Delete(T.getroot(),num));
          outfile<<"Succesfull deletion\n";
        }else{outfile<<"Το στοιχείο δεν βρέθηκε";}
        T.msize();
      }else if(c=="GETSIZE"){
        outfile<<"Size of : "<<T.Getsize()<<'\n';
        T.printInorder(T.getroot());
      }
    }
    t = clock() - t;//σταματαμε τον χρονο
    outfile<<"ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ "<<c<<": "<<(float)t/CLOCKS_PER_SEC<<'\n';

    
  }else if(d=="HASHTABLE"||d=="HASHTABLE "){
    t = clock();
     Hashtable HT;
    if(c=="BUILD"){
      flHASH=1; 
      HT.Build(f);
    }
    if(flHASH){
      if(c=="GETSIZE")
        outfile<<"SIZE: "<<HT.GetSize()<<'\n';
      else if(c=="INSERT")
        HT.Insert(num);
      else if(c=="SEARCH")
        outfile<<"SEARCH: "<<HT.Search(num)<<'\n';
    }
    t = clock() - t;
    outfile<<"ΧΡΟΝΟΣ ΕΚΤΕΛΕΣΗΣ "<<c<<": "<<(float)t/CLOCKS_PER_SEC<<'\n';
  }
  }
outfile.close();
myfile.close();  //Τέλος κλείνω τα αρχεία που είχα ανοίξει

}