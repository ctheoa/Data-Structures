#include <string>
#include "Graph.h"
#include <iostream>
#include <fstream>
#include "Node.h"
#include "Edge.h"

using namespace std;
Graph::Graph(){}

void Graph::Build(string file)
{
  ifstream infile;
    string str;
    size=0;//αρχικοποιουμε τον αριθμο των κόμβων στο 0
    infile.open(file);
    int a,b,w,j,i=0;
    capacity=1000;//χωριτικότητα αρχική 1000
    g=new Node*[capacity];
    while(infile>>a>>b>>w){//διαβάζουμε απο το αρχείο τον κόμβο1 κομβο2 και το βαρος τους
      if(size>=capacity/2){
        capacity*=2;
        Node **temp=new Node*[capacity];
        for(j=0;j<size;j++){//αν οι κόμβοι που εισαχθουν ξεπερσουν το capacity τοτε το διπλασιζουμε 
          temp[j]=g[j];
        }
        delete[] g;
        g=new Node*[capacity];
        g=temp;

        for(j=0;j<size;j++){
          Edge *temp2 = new Edge[capacity];// το ίδιο κάνουμε και για τα edges δηλαδή τους γείτονες 
          for(int k=0;k<g[j]->ecount;k++)
            temp2[k]=g[j]->e[k];
          delete[] g[j]->e;
          g[j]->e=new Edge[capacity];
          g[j]->e=temp2;
          
        }
        
      }
      // int s1=0,pos1=0,pos2=0,s2=0;
      bool flag1=false;
      bool flag2=false;
      int thesi1,thesi2;
      for(int p  =0;p<size;p++)
        {
        if (g[p]->Getnumb()==a){//βρίσκουμε τη θεση του πρωτου κόμβου στον πίνακα των κόμβων
           thesi1 = p;//η θέση του στον g 
          flag1=true;}
        if(g[p]->Getnumb()==b){//βρίσκουμε τη θεση του δεύτερου κόμβου στον πίνακα των κόμβων
           thesi2 = p; // η θέση του στον g
          flag2=true;}
        }
      if(flag1==false){//Αν δεν βρέθηκε στον στονπίνακα τότε δημιουργώ καινούριο Κόμβο
        g[size] = new Node(a);
        
        thesi1 = size;
        size=size+1;
      }
      if(flag2 ==false)//Αν δεν βρέθηκε στον στονπίνακα τότε δημιουργώ καινούριο Κόμβο
      {
        g[size] = new Node(b);
        
        thesi2= size;
        size = size+1;
      }
      bool flag = false;
      for(int p =0;p<g[thesi1]->ecount;p++)
      {
        if(g[thesi1]->e[p].Getv()->Getnumb()==b)//ελέγχουμε αν ο b υπάρχει ήδη ωσ γείτονας του a
        {
          flag = true;
        }
      }
      if(flag==false){//αν δεν είναι γείτονας τον κάνουμε γείτονα
        g[thesi1]->e[g[thesi1]->ecount].Setv(g[thesi2]);//βαζουμε ωσ γείτονα- τελικος κόμβος στη ακμη τον κόμβο που βρίσκεται στον πίνακα g και έχει όνομα b
        g[thesi1]->e[g[thesi1]->ecount].Setw(w);//εισάγω το βαρός της ακμής
        g[thesi1]->ecount+=1;//αυξάνω τη ποσοτητα των γειτωνων δηλαδή ακμων απο αυτον τον κόμβο
      }
      flag=false;
      for(int p =0;p<g[thesi2]->ecount;p++)//κανουμε την ίδια διαδικασία για τον a
      {
        if(g[thesi2]->e[p].Getv()->Getnumb()==a)
          flag = true;
      }
      if(flag==false){
        g[thesi2]->e[g[thesi2]->ecount].Setv(g[thesi1]);
        g[thesi2]->e[g[thesi2]->ecount].Setw(w);
        g[thesi2]->ecount+=1;
      }

      i++;
    }
    for(i=0;i<size;i++)
      {
        cout<<"Κόμβος "<<g[i]->Getnumb()<<"\n";	
        for(j=0;j<g[i]->ecount;j++)
          cout<<g[i]->e[j].Getv()->Getnumb()<<","<<g[i]->e[j].Getw()<<" \n";

      }

   infile.close();
}


int Graph::shortest_path(int arxi, int telos) {//αλγόριθμος Dijkstra
    
    int thesi1 = -1;
    int thesi2 = -1;
    int INF = 10000;// αναπαριστούμε το άπειρο με ένα μεγάλο αριθμό
    // Αρχικοποίηση των κόμβων
    for (int i = 0; i < size; i++) {// ψάνχω να βρω τους κόμβους στον g  
        if (g[i]->Getnumb() == arxi)
            thesi1 = i;
        if (g[i]->Getnumb() == telos)
            thesi2 = i;
        g[i]->visited = false;//λεω πωσ δεν έχει επισκεφτεί κανένας ακόμα
        g[i]->dist = INF;//η απόσταση απο τον αρχικό κόμβο μας είναι άπειρο
    }

    if (thesi1 == -1 || thesi2 == -1)
        return -1; // Αν δεν βρεθούν οι κόμβοι arxi και telos

    g[thesi1]->dist = 0;//προφανώς η απόσταση του αρχικού κόμβου με τον ευατό του είναι 0

    for (int count = 0; count < size; count++) {
        // Βρίσκουμε τον κόμβο με την ελάχιστη απόσταση που δεν έχει επισκεφτεί ακόμα
        int min = INF;
        int u = -1;

        for (int i = 0; i < size; i++) {
            if (!g[i]->visited && g[i]->dist < min) {//βρίσκουμε το μικρότερο dist
                min = g[i]->dist;
                u = i;
            }
        }

        if (u == -1)
            break; // Όλοι οι κόμβοι που μπορούν να επισκεφτούν έχουν επισκεφτεί

        g[u]->visited = true;//παμε να επισκεφτούμε αυτόν τον κόμβο όποτε σημειώνουμε οτι τον επισκεφτήκαμε

        // Ενημερώνουμε τις αποστάσεις των γειτονικών κόμβων του u
        for (int j = 0; j < g[u]->ecount; j++) {
            Node* v = g[u]->e[j].Getv();//όλοι οι γείτονες του min
            if (!v->visited && g[u]->dist + g[u]->e[j].Getw() < v->dist) {//αν δεν τον εχουμε επισκεφτεί και η αποσταση αυτουνου απο τον τον αρχικό μας κόμβο + το βαρος της ακμης με τον γείτονα του min είναι μικρότερο απο το εκάστοτε dist
                v->dist = g[u]->dist + g[u]->e[j].Getw();//τοτε ενημερώνουμε τη αποσταση δηλαδη το dist
            }
        }
    }

    return g[thesi2]->dist;//οπότε επιστρέφει τη αποσταση που τελικου κόμβου χρησιμοποιώντας των πινακα των κόμβων μας g
}

int *Graph::GetSize(){//επιστρέφει τον αριθμό των κόμβων και των ακμών του γράφου
  int *A = new int[2];
  int sum = 0;
  for(int i=0;i<size;i++)
  {
    sum = sum + g[i]->ecount;
  }
  A[0] = size;//οι κόμβοι
  A[1] = sum/2;//οι ακμες αφου εμφανίζονται δύο φορες κάθε φορά
  return A;//γυρίζουμε τον πίνακα και αυτα τα δύο μέσα
}


void Graph::Insert(int a, int b,int w)//α αρχικος β τελικος κομβος και w βαρος
{
  if(size + 2>=capacity/2){//κανουμε το ίδιο ότι και στην build
    capacity*=2;
    Node **temp=new Node*[capacity];
    for(int j=0;j<size;j++){
      temp[j]=g[j];
    }
    delete[] g;
    g=new Node*[capacity];
    g=temp;

    for(int j=0;j<size;j++){
      Edge *temp2 = new Edge[capacity];
      for(int k=0;k<capacity/2;k++)
        temp2[j]=g[j]->e[k];
      delete g[j]->e;
      g[j]->e=new Edge[capacity];
      g[j]->e=temp2;
    }
  }
  bool flag1=false;
  bool flag2=false;
  int thesi1,thesi2;
  for(int p  =0;p<size;p++)
    {
    if (g[p]->Getnumb()==a){
       thesi1 = p; 
      flag1=true;}
    if(g[p]->Getnumb()==b){
       thesi2 = p; 
      flag2=true;}
    }
  if(flag1==false){
    g[size] = new Node(a);
    thesi1 = size;
    size=size+1;
  }
  if(flag2 ==false)
  {
    g[size] = new Node(b);
    thesi2= size;
    size = size+1;
  }
  bool flag = false;
  for(int p =0;p<g[thesi1]->ecount;p++)
  {
    if(g[thesi1]->e[p].Getv()->Getnumb()==b)
    {
      flag = true;
    }
  }
  if(flag==false){
    g[thesi1]->e[g[thesi1]->ecount].Setv(g[thesi2]);
    g[thesi1]->e[g[thesi1]->ecount].Setw(w);
    g[thesi1]->ecount+=1;
  }
  flag=false;
  for(int p =0;p<g[thesi2]->ecount;p++)
  {
    if(g[thesi2]->e[p].Getv()->Getnumb()==a)
      flag = true;
  }
  if(flag==false){
    g[thesi2]->e[g[thesi2]->ecount].Setv(g[thesi1]);
    g[thesi2]->e[g[thesi2]->ecount].Setw(w);
    g[thesi2]->ecount+=1;
  }
  for(int i=0;i<size;i++)
    {
      cout<<"Κόμβος "<<g[i]->Getnumb()<<"\n";	
      for(int j=0;j<g[i]->ecount;j++)
        cout<<g[i]->e[j].Getv()->Getnumb()<<","<<g[i]->e[j].Getw()<<" \n";

    }
}

void Graph::Delete(int a,int b,bool *non)//διαγραφής της ακμης που αρχίζει με τον κόμβο α και τελειώνει στον κόμβο β
{
  cout<<"{"<<a<<","<<b<<"}"<<endl;
  bool flag1=false;
  bool flag2=false;
  int thesi1,thesi2;
  for(int p  =0;p<size;p++)//βρίσκουμε τη θέση τους στον πίνακα g
    {
    if (g[p]->Getnumb()==a){
       thesi1 = p; 
      flag1=true;}
    if(g[p]->Getnumb()==b){
       thesi2 = p; 
      flag2=true;}
    }
  if (flag1 && flag2)//αν υπάρχουν και τα δυο 
  {
    for(int i=0;i<g[thesi1]->ecount;i++)
    {
      if(g[thesi1]->e[i].Getv()->Getnumb()==b)//μόλις βρουμε το β στους γειτονες του α
      {
      for(int k = i;k<g[thesi1]->ecount-1;k++)
        g[thesi1]->e[k] = g[thesi1]->e[k+1];//κανουμε shift τα στοιχεια
      g[thesi1]->ecount -= 1;//και μειωνιυμε τον αριθμο των γειτόνων
      *non = false;
      break;
      }
    }
    *non = true;//αν η ακμη υπάρχει
    for(int i=0;i<g[thesi2]->ecount;i++)
      {
        if(g[thesi2]->e[i].Getv()->Getnumb()==a){//μόλις βρουμε το α στους γειτονες του β
        for(int k = i;k<g[thesi2]->ecount-1;k++)
          g[thesi2]->e[k] = g[thesi2]->e[k+1];//κανουμε shift τα στοιχεια
        g[thesi2]->ecount -= 1;//και μειωνιυμε τον αριθμο των γειτόνων
        *non = false;
          break;
        }
      }
  
  if (g[thesi1]->ecount == 0){//αν ήταν ο β ο μοναδικός γείτονας του a τοτε πρεπει να αφαιρεσω στον α απο τον πινακα με τους κόμβους 
    for (int i = thesi1;i<size-1;i++)
      g[i] = g[i+1];
    size = size-1;
    thesi2 = thesi2-1;
  }
  if (g[thesi2]->ecount == 0){//αν ήταν ο α ομοναδικός γείτονας του a τοτε πρεπει να αφαιρεσω στον α απο τον πινακα με τους κόμβους 
    for (int i = thesi2;i<size-1;i++)
      g[i] = g[i+1];
    size = size -1;
  }
  for(int i=0;i<size;i++)
    {
      cout<<"Κόμβος "<<g[i]->Getnumb()<<"\n";	
      for(int j=0;j<g[i]->ecount;j++)
        cout<<g[i]->e[j].Getv()->Getnumb()<<","<<g[i]->e[j].Getw()<<" \n";
    }
  }else
    *non = true;
    
  
}


void Graph::DFS(int v)//DFS
{
  int thesi = -1,thesi2 = -1,nn;
  for (int i = 0;i<size;i++)
  {
    if (g[i]->Getnumb() == v)//βρίσκουμε που είναι ο κόμβος απο τον οποίον θα ξεκινήσουμε το DFS στον g
      thesi  = i;
  }
  g[thesi]->visited = true;//τον σημειώνουμε ότι τον επισκεφτηκαμε
  for(int i =0;i<g[thesi]->ecount;++i)
  {
     nn =  g[thesi]->e[i].Getv()->Getnumb();//για καθε γειτονα βρίκω τη θεση του στον g
    for (int j= 0;j<size;j++)
      {
        if (g[j]->Getnumb() == nn)//βρισκω που είναι ο κόμβος στον g
          thesi2  = j;
      }
    if(!g[thesi2]->visited){//αν δεν το εχουμε επισκεφτει κανουμε και γι αυτον dfs
      DFS(nn);
    }
  }
}

int Graph::CCC(){//συνδεδεμένες συνιστώσες
  for(int v =0 ;v<size;v++)
    g[v]->visited=false;

  int count = 0;
  for(int v =0;v<size;v++)//για όλους τους κόμβους κανω dfs ωστε να δω αν καποιος απο αυτους ανηκει σε διαφορετική συνιστωσα
  {
    if(!g[v]->visited)
    {
      DFS(g[v]->Getnumb());
      count ++;
    }
  }
  return count;
}



int Graph::min_span_tree(){//αλγόριθμος Kruskal
  cout<<"mphke\n";
  
  int totalEdges = 0;//o αριθμός των συνολικων ακμων
  for(int i =0;i<size;i++)
    totalEdges += g[i]->ecount;
  totalEdges = totalEdges/2;
  cout<<totalEdges<<endl;
  Edge *edges = new Edge[totalEdges];//φτιάχνουμε εναν πίνακα που θα έχει όλες τις ακμες μεσα
  int index = 0;
  for(int i=0;i<size;i++){//σε αυτη τη διπλη επαναάηψη εκχωρούμε τις ακμες μεσα στο πινακα σιγουρεύοντας ότι δεν εχει ξανα προστεθει μέσα η ίδια ακμη
    
    for(int j =0;j<g[i]->ecount;j++){
      
      if (check(i,j,edges,index) == false)
      {
        
        edges[index] = g[i]->e[j];
        cout<<g[i]->Getnumb()<<" "<<g[i]->e[j].Getv()->Getnumb()<<" "<<g[i]->e[j].Getw()<<endl;
        edges[index].Setsrc(g[i]->Getnumb());//η Setsrc είναι προαιρετικη αλλα μασ βοηθάει να μορφοποιήσουμε το προβλημα καλύτερα και να το κατανοησουμε
        index= index + 1;
      }
    }
  }
  cout<<"\n";
  
  quicksort(edges,0,totalEdges-1);//ταξινόμηση των ακμων 
  
  for(int i=0;i<totalEdges;i++)
    cout<<edges[i].Getsrc()<<" "<<edges[i].Getv()->Getnumb()<<" "<<edges[i].Getw()<<endl;
  cout<<'['<<totalEdges<<" "<<index<<"]"<<endl;
  int *parent = new int[size];//κατασκευάζουμε έναν πινακα όπου η θεση του u στον g θα σηματοδοτει το σε ποια θεση του parent θα αποθηκευτει
  for(int i = 0;i<size;i++)
    parent[i]=i;
  
  int totalWeight = 0;
  
  for(int i =0;i<index;i++){//για όλες τις ακμές
    int u = edges[i].Getsrc();//αρχικός κόμβος
    int v = edges[i].Getv()->Getnumb();//τελικός κόμβος
    int setU = find_parent(parent,u);//εστω οτι δημιουργούμε καινουρια συνολα για καθε κόμβο 
    int setV = find_parent(parent,v);
    if (setU != setV){//αν δεν είναι στο ιδιο συνολο δηλαδη δεν έιναι χρωματισμενα ιδια τοτε
      totalWeight += edges[i].Getw();//αυξανει το βαρος του MST
      union_parent(parent,setU,setV);//τα εννοννω στο δεντρο μου
    }
  }
  delete[] edges;
  delete[] parent;
  return totalWeight;
}



int Graph::find_parent(int *parent,int num){//βρισκουμε το 'γονεα' - αρχικό κόμβο με την αναδρομη 
  if (parent[num] != num)
    parent[num] = find_parent(parent,parent[num]);
  return parent[num];
}

void Graph::union_parent(int *parent,int x,int y){//εννονουμε τα συνολα
  int setX = find_parent(parent,x);
  int setY = find_parent(parent,y);
  if (setX < setY){//για το τελικο mst για να μην αυξηθουν τα υψη (αν και στη προκειμενη περιπτωση που γυρναμε μονο το βαρος δεν χρειαζεται)
    parent[setY] = setX;
  }else if(setX>setY){
    parent[setX] = setY;
  }
}


bool Graph::check(int i,int j,Edge *edges,int totalEdges){//ελέγχουμε αν υπάρχει ήδη μεσα η ακμη 
  int src = g[i]->Getnumb();
  int dest = g[i]->e[j].Getv()->Getnumb();
  for(int k =0;k<totalEdges;k++){
    if ((edges[k].Getsrc() == src && edges[k].Getv()->Getnumb() == dest) || (edges[k].Getsrc() == dest && edges[k].Getv()->Getnumb() == src))
      return true;
    
  }
  return false;
}

int Graph::partition(Edge *arr,int low,int high,int pivot)
{
  int i = low;
  int j = low;
  while(i<=high){
    if(arr[i].Getw() > pivot)
      i++;
    else{
      Edge temp = arr[i];
      arr[i]=arr[j];
      arr[j]=temp;
      i++;
      j++;
    }
    
  }
  return j-1;
}
void Graph::quicksort(Edge *arr,int low,int high)//κανουμε quicksort
{
  if(low<high){
    int pivot = arr[high].Getw();
    int pos = partition(arr,low,high,pivot);
    quicksort(arr,low,pos-1);
    quicksort(arr,pos+1,high);
  }
}