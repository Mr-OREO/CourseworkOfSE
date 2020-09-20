#include<stdio.h>
#include<stdlib.h>

int N, L;
typedef int Element;

typedef struct BSTreeNode* BSTree;
struct BSTreeNode{
	Element Key;
	BSTree Left;
	BSTree Right;
};

BSTree BuildBST()
{
	int i = 0;
	BSTree T = NULL, Head = NULL, PTR, PPTR;
	for(i = 0; i < N; i++)
	{
		T = (BSTree)malloc(sizeof(struct BSTreeNode));
		scanf("%d", &T->Key);
		T->Left = T->Right = NULL;
		if(Head == NULL)
		{
			Head = T;
			continue;
		}
		PPTR = PTR = Head;
		while(1)
		{
			if(PTR == NULL)
				if(T->Key > PPTR->Key)
				{
					PPTR->Right = T;
					break;
				}
				else{
					PPTR->Left = T;
					break;
				}
			PPTR = PTR;
			if(PTR->Key < T->Key)
				PTR = PTR->Right;
			else PTR = PTR->Left;
		}
	}
	return Head;
}

int BSTCompair(BSTree T1, BSTree T2)
{
	if(T1 == NULL && T2 == NULL)
		return 1;
	else if(T1 == NULL || T2 == NULL)
		return 0;
	else if(T1->Key != T2->Key)
		return 0;
	int same = BSTCompair(T1->Left, T2->Left) && BSTCompair(T1->Right, T2->Right);
	return same;
 } 

void BSTCheck(BSTree T)
{
	int i, BST = 1, test;
	BSTree Test = BuildBST();
	if(BSTCompair(T, Test))
		printf("Yes\n");
	else printf("No\n");
}

int main()
{
	int i;
	while(1)
	{
		scanf("%d%d", &N, &L);
		if(N == 0)
			break;
		BSTree InitTree = BuildBST();
		for(int j = 0; j < L; j++)
			BSTCheck(InitTree);
	}
	return 0;
 } 
