#include <stdio.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>

typedef int object;
class element1 {
    public: object val;
    element1 *next;
};
class list1 {
    private: 
        element1 *head; // Zeiger auf den Anfang
        element1 *tail; // Zeiger auf das Ende
    public: 
        list1();
        ~list1();
        void Append(object o); // Fügt einen Wert hinzu
        void DeleteList(element1 *first); // Liste entfernen
        void DeleteValue(object o); // Wert entfernen
        void Print(); // Liste ausgeben
        void swap(element1 *a, element1 *b);
        void PreparePartition(list1 list, int f,int l,int &p);
        void Quicksort(list1 list, int f,int l);
};
list1::list1() {
    head=NULL; tail=NULL; 
}
list1::~list1() {
    DeleteList(head);
    head=NULL; tail=NULL; 
}
void list1::Append(object o) {
    element1 *elem=new element1;
    elem->val=o;
    elem->next=NULL;
    if (tail==NULL) {
        head=elem; tail=elem;
    } else {
        tail->next=elem; tail=elem;
    }
}
void list1::DeleteValue(object o) {
        element1 *curr=head, *prev=NULL;
        while (curr!=NULL) {
        if (curr->val==o) {
            !prev ? head=curr->next : prev->next=curr->next;
            if (curr==tail) tail=prev;
            element1 *h=curr; curr=curr->next;
            delete h; 
        }
        else {
            prev=curr; curr=curr->next;
        } 
    } 
}
void list1::DeleteList(element1 *first) { 
    if (first != NULL) {
        if (first->next != NULL) DeleteList(first->next);
        delete first; 
    }
}
void list1::swap(element1 *a, element1 *b)
{
    element1 *curr = head;
    element1 *preva = NULL;
    element1 *prevb = NULL;
    while (curr->next != a) {
        preva = curr;
        curr = curr->next;
    }
    while (curr->next != b) {
        prevb = curr;
        curr = curr->next;
    }
    element1 *bnext = b->next;
    preva ? preva->next = b : head = b;
    prevb->next = a;
    b->next = a->next;
    bnext ? a->next = bnext : tail = a;
}

int main() {
    list1 list;
    const int n = 10;

    srand(time(0));

    for (int i = 0; i  < n; i++) {
        object o = rand() % 51;
        list.Append(o);
    }

    list.Print();
    list.Quicksort(list, 1, n);

    return 0;
}