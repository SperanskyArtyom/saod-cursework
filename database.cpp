#include "database.h"

#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

void printRecord(Record rec){
    cout << setw(31) << rec.depositor << setw(15)<< rec.amount
         << setw(15) << rec.date << setw(23) << rec.lawyer << endl;
}

void showDatabase(Record **dataBase){
    system("cls");
    int ch = 0;
    int i = 0;
    while(true){
       cout << "Esc - назад\n\n1 - предыдущая страница\n2 - следующая страница\n\n";
       cout <<'\t' << left <<setw(31) << "ФИО вкладчика" << setw(15) << "Сумма вклада"
            << setw(15) << "Дата вклада" << setw(23) << "ФИО адвоката" << endl;
        for (int k = 0; k < 20; k++){
        	if (i+k >= 0 && i+k < 4000){
            	cout << i + k + 1 << '\t';
            	printRecord(*dataBase[i+k]);
        	}
        }
        ch = _getch();

        if (ch == 27)
            break;
        if (ch == '2')
			if (i + 20 >= 4000)
				i = 3980;
            else i += 20;
        else if (ch == '1')
        	if (i - 20 < 0)
        		i = 0;
            else i -= 20;
        else if (ch == '№' || ch == '#')
        {	
        	cout << "\n#";
        	int number;
        	cin >> number;
        	if (number > 0 && number <= 4000)
        		i = number - 1;
		}
        system("cls");
    }
}

void showDatabase(Record *dataBase){
    system("cls");
    int ch = 0;
    int i = 0;
    while(true){
       cout << "Esc - назад\n\n1 - предыдущая страница\n2 - следующая страница\n\n";
       cout <<'\t' << left <<setw(31) << "ФИО вкладчика" << setw(15) << "Сумма вклада"
            << setw(15) << "Дата вклада" << setw(23) << "ФИО адвоката" << endl;
        for (int k = 0; k < 20; k++){
        	if (i+k >= 0 && i+k < 4000){
            	cout << i + k + 1 << '\t';
            	printRecord(dataBase[i+k]);
        	}
        }
        ch = _getch();

        if (ch == 27)
            break;
        if (ch == '2'){
			if (i + 20 >= 4000)
				i = 3980;
            else i += 20;
        }
        else if (ch == '1' && (i - 20 >= 0))
            i -= 20;
        else if (ch == '№' || ch == '#')
        {
        	cout << "\n#";
        	int number;
        	cin >> number;
        	if (number > 0 && number <= 4000)
        		i = number - 1;
		}
        system("cls");
    }
}
