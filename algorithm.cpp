#include "algorithm.h"

#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <cstring>

date stringToDate(Record rec){
    date result;
    char buf[10];
    memcpy(buf, rec.date, 2);
    result.day = atoi(buf);
    memcpy(buf, &rec.date[3], 2);
    result.mounth = atoi(buf);
    memcpy(buf, &rec.date[6], 2);
    result.year = atoi(buf);
    
    return result;
}

int compAmount(Record rec1, Record rec2){
    if (rec1.amount < rec2.amount)
        return -1;
    if (rec1.amount > rec2.amount)
        return 1;
    return 0;
}

int compDate(Record rec1, Record rec2){
    date d1 = stringToDate(rec1);
    date d2 = stringToDate(rec2);
    if (d1.year < d2.year)
        return -1;
    if (d1.year > d2.year)
        return 1;
    if (d1.mounth < d2.mounth)
        return -1;
    if (d1.mounth > d2.mounth)
        return 1;
    if (d1.day < d2.day)
        return -1;
    if (d1.day > d2.day)
        return 1;
    return 0;
}

int comp(Record rec1, Record rec2){
    int a = compAmount(rec1, rec2);
    if (a != 0)
        return a;
    return compDate(rec1, rec2);
}

int treeComp(Record rec1, Record rec2){
	int depositor_compare = strncmp(rec1.depositor, rec2.depositor, 29);
	return depositor_compare;
}

void QuickSort(Record** indexArr, int left, int right, int (*comparator)(Record, Record)){
    while (left < right) {
        Record x = *indexArr[(left+right)/2];
        int i = left, j = right;
        while (i <= j) {
            while (comparator(*indexArr[i], x) < 0)
                i++;
            while (comparator(*indexArr[j], x) > 0)
                j--;
            if (i <= j){
                Record *temp = indexArr[i];
                indexArr[i] = indexArr[j];
                indexArr[j] = temp;
                i++;
                j--;
            }
        }
        if (j - left < right - i){
            QuickSort(indexArr, left, j, comparator);
            left = i;
        } else{
            QuickSort(indexArr, i, right, comparator);
            right = j;
        }
    }
}

void QuickSort(Record** indexArr, int (*comparator)(Record, Record)){
    QuickSort(indexArr, 0, 3999, comparator);
}

void fillIndexArray(Record* database, Record** indexArr){
    for (int i = 0; i < 4000; i++)
        indexArr[i] = &database[i];
}

Queue BSearch (Record** indexArr, int size, unsigned short key)
{
    Queue q = initQ();
    int L = 0, R = size - 1;
    while (L < R){
        int m = floor((double)(L + R) / 2);
        if (indexArr[m]->amount < key)
            L = m + 1;
        else
            R = m;
    }
    if (indexArr[R]->amount == key) {
        add(q, *indexArr[R]);
        R++;
        while (R < size && indexArr[R]->amount == key) {
            add(q, *indexArr[R]);
            R++;
        }
    }
    return q;
}
