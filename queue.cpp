#include "queue.h"

#include <iostream>
#include <cstdlib>

// Stack functions

void add(List *&head, Record data){
    List *p = new List;
    p->data = data;
    p->next = head;
    head = p;
}

void pop(List *&head){
    List *p = head;
    head = head->next;
    delete p;
}

void clear(List *&head){
    while (head != NULL)
        pop(head);
}
// Queue

Queue initQ(){
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    return q;
}

void add(Queue &q, Record n){
    List *p = new List;
    p->data = n;
    p->next = NULL;
    if (q.head != NULL)
        q.tail->next = p;
    else q.head = p;
    q.tail = p;
}
