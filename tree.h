#pragma once

#include "database.h"
#include <cstddef>

struct Tree
{
    Record *data;
    int weight;
    struct Tree* left = NULL;
    struct Tree* right = NULL;
};

Tree *createDOP(Record* arr[], int n);
Record *search(Tree *root, char key[], int n);
