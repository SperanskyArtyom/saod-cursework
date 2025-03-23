#pragma once

#include "database.h"
#include "queue.h"

int comp(Record, Record);
int treeComp(Record rec1, Record rec2);
void fillIndexArray(Record* database, Record** indexArr);
void QuickSort(Record** indexArr, int (*comparator)(Record, Record));
void QuickSort(Record** indexArr, int left, int right, int (*comparator)(Record, Record));
Queue BSearch (Record** indexArr, int size, unsigned short key);
