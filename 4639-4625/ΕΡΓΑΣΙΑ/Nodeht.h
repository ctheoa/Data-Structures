#ifndef NODEHT_H
#define NODEHT_H

class Nodeht{
private:
 int value; //η τιμή του κόμβου
 Nodeht* next;  //ο επόμενος κόμβος
public:
 Nodeht(int a);  //κατασκεθατσής
 int GetValue();  //επιστρέφει τη τιμή του κόμβου
 void SetNext(Nodeht* next);  //βάζει ως επόμενο κόμβο τον next
 Nodeht* GetNext();  //επιστρέφει τον επόμενο κόμβο
};

#endif