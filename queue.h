#pragma once

#include "database.h"

typedef struct tLE{
    struct tLE* next;
    Record data;
}List;

typedef struct qu{
    List *head;
    List *tail;
}Queue;

// Stack functions

void add(List *&head, Record data);
void pop(List *&head);
void clear(List *&head);

// Queue
Queue initQ();
void add(Queue &q, Record n);
