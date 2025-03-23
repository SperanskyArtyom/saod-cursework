#include "tree.h"
#include "algorithm.h"

#include <cstdlib>
#include <cstring>

void addRST_R(Tree *&p, Tree newVertex)
{
    if (p == NULL)
    {
        p = new Tree;
        p->data = newVertex.data;
        p->left = NULL;
        p->right = NULL;
    }
    else if (treeComp(*newVertex.data, *(p->data)) <= 0)
    {
        addRST_R(p->left, newVertex);
    }
    else if (treeComp(*newVertex.data, *(p->data)) > 0)
    {
        addRST_R(p->right, newVertex);
    }
}

void A2(Tree *&p, int L, int R, Tree V[])
{
    int wes = 0, sum = 0;
    if (L <= R)
    {
        int i = 0;
        for (i = L; i < R; i++)
            wes = wes + V[i].weight;

        for (i = L; i < R; i++)
        {
            if ((sum <= wes / 2) && (sum + V[i].weight > wes / 2))
                break;
            sum = sum + V[i].weight;
        }
        addRST_R(p, V[i]);
        A2(p, L, i - 1, V);
        A2(p, i + 1, R, V);
    }
}

Tree *createDOP(Record *arr[], int n)
{
    Tree V[n];
    for (int i = 0; i < n; i++)
    {
        V[i].data = arr[i];
        V[i].weight = rand() % 1001;
    }
    Tree *root = NULL;
    A2(root, 0, n - 1, V);
    return root;
}

Record *search(Tree *root, char key[], int n){
	Tree *p = root;
	while (p != NULL){
		int comparison = strncmp(key, p->data->depositor, n);
		if (comparison == 0)
			return p->data;
		if (comparison < 0)
			p = p->left;
		else if (comparison > 0)
			p = p->right;
	}
	return NULL;
}
