#include <iostream>
#include "tree.h"
#include <fstream>
using namespace std;

tree::tree(){}

void tree::Build(string str)
{
  int tmpsize;
  root=nullptr;//αρχικοποιηση ρίζα σε null
  size = 0;//0 κόμβοι αρχικά
  ifstream infile;
  infile.open(str);
  int a,i=0,capacity=1000;//εστω μια αρχική χωριτικότητα κόμβων
  arr=new int [1000];//πίνακας των κόμβων 

  while(infile>>a){
    if(i>=capacity){// αν το ξεπεράσει τον διπλασιάζουμε
      capacity*=2;
      int *temp=new int[capacity];
        for(int j=0;j<i;j++)
          temp[j]=arr[j];
      delete[] arr;
    arr=temp;
  }
  arr[i]=a;//προσθήκη κόμβου 
  i++; 
  }
  infile.close();  
  tmpsize=i;//κανουμε το size όσο με τα στοιχεια που μας δόθηκαν στο .txt
  int k;


  for(k=0;k<tmpsize;k++){
      if (search(arr[k])=="FAILURE"){
        size = size+1;
       root = this->Insert(root,arr[k]);}//εισάγουμε κατάλληλα τα στοιχεια στο δέντρο
      // cout<<"["<<arr[k]<<"]\n";
  }
  delete[] arr;
  cout<<"!!!!"<<root->Getnumb()<<"!!!!\n";
}


Node *tree::Insert(Node *n,int v)
{
  
  if(n==nullptr){//αυτη η περίπτωση καλύπτει τη ρίζα καθως και στις αναδρομές όταν φτάσει στο σωστο σημείο για να γίνει η εισαγωγή
    n=new Node(v);
    n->Setnumb(v);
    n->Setl(nullptr);
    n->Setr(nullptr);
    return n;
  }else if (v<n->Getnumb()){// αν το στοιχειο πρεπει να εισαχθεί πιο αριστερά αφου είναι μικρότερο απο τον κομβο εκεινη τη στιγμή
    n->Setl(Insert(n->Getl(),v));//κανω τη ρίζα το αριστερο παιδι και ξανακανω τη διαδικασια
    n = Calc_bf(n);//αλλαγή ισορροποιας
  }else if (v>=n->Getnumb()){//αν το στοιχειο πρεπει να εισαχθεί πιο αριστερά αφου είναι μικρότερο απο τον κομβο εκεινη τη στιγμή
    n->Setr(Insert(n->Getr(),v));//κανω τη ρίζα το αριστερο παιδι και ξανακανω τη διαδικασια
    n = Calc_bf(n);//αλλαγή ισορροποιας
  } return n;
}


int tree::Calc_h(Node *n)
{
  int h=0;
  if(n!= nullptr){
    int l_h = Calc_h(n->Getl());//αναδρομικά βρίσκω το ύψος του αριστεροθ παιδιου 
    int r_h = Calc_h(n->Getr());//αναδρομικά βρίσκω το ύψος του δεξιου παιδιου
    int max_h = maximum(l_h,r_h);//βρισκω το μεγαλύτερο απο τα δύο
    h = max_h +1;
  }
  return h;
}


int tree::diafora(Node *n)
{
  int l_h = Calc_h(n->Getl());//αναδρομικά βρίσκω το ύψος του αριστερου παιδιου
  int r_h = Calc_h(n->Getr());//αναδρομικά βρίσκω το ύψος του δεξιου παιδιου
  int bf = l_h - r_h;//υπολογίζω την ισοροποια
  return bf;
}

Node *tree::leftrotate(Node *parent)//αριστερή περιστροφή
{
  Node * n;
  n = parent->Getr();//εστω n το δεξίο υπόδεντρο του κόμβου 
  parent->Setr(n->Getl());//το αριστερό υπόδεντρο του δευτερου κόμβου δηλαδη του n γίνεται πλεον το δεξίο παιδί του αρχικού κόμβου 
  n->Setl(parent);//πλεον το n ειναι η ρίζα και το parent γινεται το αριστερο παιδι του
  return n;
}

void tree::Setroot(Node *root){this->root = root;}//setter για τη ρίζα
Node *tree::getroot(){return root;}//getter για τη ρίζα
void tree::addsize(){size = size +1;}//αυξάνουμε το size κατα ενα (για την εισαγωγή κόμβων)

Node *tree::rightrotate(Node *parent)//δεξία περιστροφή
{
  Node *n;
  n = parent->Getl();//εστω n το αριστερο υπόδεντρο του κόμβου 
  parent->Setl(n->Getr());//το δεξιό υπόδεντρο του δευτερου κόμβου δηλαδη του n γίνεται πλεον το αριστερό παιδί του αρχικού κόμβου 
  n->Setr(parent);//πλεον το n ειναι η ρίζα και το parent γινεται το δεξιό παιδι του
  return n;
}

Node *tree::lrrotate(Node *parent)
{
  Node *n;
  n = parent->Getl();//παίρνω το αριστερό παιδί του κόμβου μας 
  parent->Setl(leftrotate(n));//και μετα κανω γι αυτο μια αριστερή περιστροφη ώστε μετα να κανω μια δεξία για τον αρχικό δέντρο 
  return rightrotate(parent);
}

Node *tree::rlrotate(Node *parent)
{
  Node *n;
  n = parent->Getr();//παίρνω το δεξιό παιδί του κόμβου μας 
  parent->Setr(rightrotate(n));//και μετα κανω γι αυτο μια δεξία περιστροφη ώστε μετα να κανω μια αριστερά για τον αρχικό δέντρο 
  return leftrotate(parent);
}

Node *tree::Calc_bf(Node *parent)
{
  int bf = diafora(parent);//υπολογίζουμε την ισορροποία του κόμβου με βάση τα ύψη
  if (bf > 1){// τοτε το δεντρο είναι αριστερά βαρή
    if(diafora(parent->Getl()) > 0)//τωρα για το αριστερό του παιδί ελέγχουμε τη ισορροποια με βάση τα ύψη, αν ειναι >0 τοτε χρειάζεται μονο μια δεξιά περιστροφή 
      parent = rightrotate(parent); 
    else
      parent = lrrotate(parent);//αλλιως χρειάζεται μια αριστερή και μετα μια δεξιά περιστροφή
  }else if(bf<-1){//τοτε το δέντρο είναι δεξιά βαρή
    if (diafora(parent->Getr()) > 0)// αν η ισορροπία είναι >0 τοτε χρειάζεται μια δεξία στο δεξι παιδί και μια αριστερή στον κόμβο αυτο 
      parent = rlrotate(parent);
    else
      parent = leftrotate(parent);//αλλιωσ απλα μια αριστερή περιστροφή
  }
      
  return  parent;
}

string tree::search(int key)
{
  cout<<"μπηκει στην σερτσ\n";
  Node *node_now_numb = this->root;//αρχικοποιω την τωρινή μου ρίζα δηλαδή γονές με τη ρίζα του δέντρου

  if (root == nullptr)//αν το δεντρο ειναι κενο προφανώς δεν βρέθηκε το στοιχείο
    return "FAILURE";

  while (node_now_numb!=nullptr)
    if (node_now_numb->Getnumb() == key )//αν βρέθηκε επιστρέφει success
      return "SUCCESS";
    else{
      if (key < node_now_numb->Getnumb())//αν το στοιχείο είναι μικρότερο απο τον γονέα τοτε παμε πιο αριστερά 
        node_now_numb = node_now_numb->Getl();
      else 
        node_now_numb = node_now_numb->Getr();//αλλιωσ δεξιά
      }    

    return "FAILURE";//αν ψαξαμε όλο το δεντρο και δεν το βρήκαμε επιστρέφουμε failure
}

Node *tree::Findmin(Node *n)//όπου n η ρίζα του δέντρου 
{
  while (n->Getl()!=nullptr)//για να βρουμε το μικρότερο παμε όσο πιο αριστερά γινεται στο δέντρο
  {
    n=n->Getl();
  }
  return n;
}
int tree::Getsize()//ο αριθμός των κόμβων είναι στο size 
{
  return size;
}

Node *tree::Delete(Node *n, int numb)
{
  if (n == nullptr)// αν το δέντρο είναι άδειο επιστρέφω null
    return n;
  if (numb < n->Getnumb())
    n->Setl(Delete(n->Getl(), numb));//ψαχνω να βρω που είναι ο κόβμος με όνομα numb πηγαίνοντασ αριστερά 
  else if(numb>n->Getnumb())
    n->Setr(Delete(n->Getr(), numb));//ψαχνω να βρω που είναι ο κόβμος με όνομα numb πηγαίνοντασ αριστερά
  else{//αν τον βρω παω εδώ 
    if (n->Getl() == nullptr){//αν έχει μόνο δεξί παιδί
      Node *temp = n->Getr();
      delete n;
      return temp;// επιστρέφουμε το δεξί παιδί ώστε να συνδεθεί με τον προηγούμενο κόμβο
    }else if (n->Getr() == nullptr){//αν έχει μόνο αριστερό παιδί
      Node *temp = n->Getl();
      delete n;
      return temp;// επιστρέφουμε το αριστερό παιδί ώστε να συνδεθεί με τον προηγούμενο κόμβο
    }
    Node *temp = Findmin(n->Getr());//όποτε για να διατηρήουμε την ''δυαδικότητα δέντρων αναζήτησης''  παμε να βρουμε τον μικρότερο κόμβο απο τα δεξία του κόμβου που θέλαμε να διαγράψοθυμε και να τον βάλουμε στη θεση του κόμβου αυτου για να το κανουμε τη ''ρίζα'' του υπόδεντρου με όλα τα άλλα δεξιά υπόδεντρα να είναι μικρότερα από αυτό.

    n->Setnumb(temp->Getnumb());
    n->Setr(Delete(n->Getr(), temp->Getnumb()));//μετά διαφράφουμε το κόμβο που προσθεσαμε πριν
  }
  return Calc_bf(n);//υπολογίζουμε και επιστρέφουμε τον νεο ισορροπημένο κόμβο
}
void tree::msize(){size = size-1;}//μειώνουμε το size κατα ένα(για την διαγραφή)

int tree::maximum(int a, int b)//βλεπω ποιός αριθμός είναι μεγαλύτερος (θα το χρειαστούμε στα ύψη)
{
  if (a>b)
    return a;
  else
    return b;
}
void tree::printInorder(Node* node)
{
    if (node == NULL)
        return;

    printInorder(node->Getl());

    cout << node->Getnumb() << " ";

    printInorder(node->Getr());
}