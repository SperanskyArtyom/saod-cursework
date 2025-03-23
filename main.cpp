#include "database.h"
#include "algorithm.h"
#include "queue.h"
#include "tree.h"
#include "shannon.h"

#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>

using namespace std;

void showDatabase(Queue q);

int main()
{
    system("cls");
    
    string filename = "testBase3.dat";
    Record* dataBase = new Record[4000], *index_inc[4000], *index_dec[4000], *index_tree[4000];
    ifstream fp("testBase3.dat", ios::binary|ios::in);
    int i = 0;

    if(fp.is_open()){
        while(fp.read((char*) &dataBase[i], sizeof(Record)))
        i++;
    }
    fp.close();
	
    fillIndexArray(dataBase, index_inc);
   
    QuickSort(index_inc, comp);
	
    for (int i = 0; i < 4000; i++){
        index_dec[i] = index_inc[3999-i];
    }
    
    while(true){
        system("cls");
        cout << "1 - ����������� ��������������� ��\n"
			 <<	"2 - ����������� ����������������� ��\n"
			 << "3 - ����� �� �����\n4 - �����������"
			 <<	"\n\nEsc - �����\n";
        int ch = _getch();
        if(ch == 27)
            break;
        else if (ch == '1')
        {
            while(true){
                system("cls");
                cout << "���������� �� ����� ������ � ����\n\n�������� �����������: 1 - �� �����������, 2 - �� ��������\n\nEsc - ��������� � ����";
                ch = _getch();
                if(ch == 27)
                    break;
                switch (ch)
                {
                case '1':
                    showDatabase(index_inc);
                    break;
                case '2':
                    showDatabase(index_dec);
                    break;
                default:
                    break;
                }
            }
        }
        else if (ch == '2'){
        	showDatabase(dataBase);
		}
        else if (ch == '3'){
        			system("cls");
                	cout << "������� ���� ������ (����� ������): ";
                	unsigned short key;
                	cin >> key;
                	Queue founded_Records = BSearch(index_inc, 4000, key);
                	if (founded_Records.head == NULL){
						cout << "��� ������� � ����� ������\n������� Esc, ����� �������� � ������� ����\n";
						while(true){
							int ch = _getch();
        					if(ch == 27)
            				break;
						}
					}
					else
                		showDatabase(founded_Records);
		}
		else if (ch == '4'){
			unsigned int totalSymbols = 0;
			vector<Symbol> symbols = calculateProbabilities(filename, totalSymbols);
	    	generateShannonCodes(symbols);
			while (true){
				system("cls");
	    		displayResults(symbols, totalSymbols);
	    		cout << "\n������� Esc, ����� ��������\n";
	    		ch = _getch();
	            if(ch == 27)
	                break;
    		}
		}
    }

    delete[] dataBase;
    return 0;
}

void queue_to_arr(Queue q, Record *arr[], int n)
{
    List *p = q.head;
    p = q.head;
    for (int i = 0; i < n; i++)
    {
        arr[i] = &(p->data);
        p = p->next;
    }
}

void print(Tree *p){
	if (p != NULL){
		print(p->left);
		printRecord(*(p->data));
		print(p->right);
	}
}

void showTree(Tree *root){
    system("cls");
	cout << left <<setw(31) << "��� ���������" << setw(15) << "����� ������"
         << setw(15) << "���� ������" << setw(23) << "��� ��������" << endl;
    print(root);
    cout << "\nEsc - �����\n1 - ����� �� ��� ���������\n";
	while (true){
        int ch = _getch();
        if (ch == 27)
        	break;
        if (ch == '1'){
        	cout << "\n������� ���� ������: ";
        	string key;
        	std::cin.ignore();
        	std::getline(std::cin, key);
        	const char *charKey = key.c_str();
        	Record* foundedRec = search(root, (char*) charKey, key.length());
        	if (foundedRec != NULL){
        		cout << '\n' << left <<setw(31) << "��� ���������" << setw(15) << "����� ������"
         			 << setw(15) << "���� ������" << setw(23) << "��� ��������" << endl;
				printRecord(*foundedRec);
			}
			else
				cout << "\n������ � ������ ������ �� �������";
			cout << "\n��� �������� ������� Esc";    
		}
    }
}

void showDatabase(Queue q){
    int ch = 0, i = 0;
    List *p1 = q.head;
    List *p2 = q.head;
    
    while(true){
    	system("cls");
    	p1 = p2;
       cout << "Esc - �����\n1 - �������� � ������ �������\n2 - ��������� ��������\n3 - ����������� ������ ������ �� ��� ���������\n\n";
       cout <<'\t' << left <<setw(31) << "��� ���������" << setw(15) << "����� ������"
            << setw(15) << "���� ������" << setw(23) << "��� ��������" << endl;
        for (int k = 0; k < 20; k++){
        	cout << i + k + 1 << '\t';
            printRecord(p1->data);
        	if (p1->next == NULL)
				break;
			p1 = p1->next;
        }
        ch = _getch();

        if (ch == 27)
            break;
        if (ch == '1'){
        	p2 = q.head;
        	i = 0;
		}
        if (ch == '2' && p1->next != NULL){
           	p2 = p1;
			i += 20;
		}
        system("cls");
        if (ch == '3'){
        	int n = 0;
        	p1 = q.head;
        	while (p1 != NULL)
            {
                n++;
                p1 = p1->next;
            }
        	Record *arr[n];
            queue_to_arr(q, arr, n);
    		QuickSort(arr, 0, n-1, treeComp);
    		Tree *root = createDOP(arr, n);
        	showTree(root);
        }
    }
    clear(q.head);
}

