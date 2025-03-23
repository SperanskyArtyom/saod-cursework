#pragma once

struct Record
{
    char depositor[30];
    unsigned short amount;
    char date[10];
    char lawyer[22];
};

struct date{
	int year;
	int mounth;
	int day;
};

void showDatabase(Record **dataBase);
void showDatabase(Record *dataBase);
void printRecord(Record rec);
