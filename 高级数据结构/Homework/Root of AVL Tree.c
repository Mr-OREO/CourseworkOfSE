#include<stdio.h>
#include<stdlib.h>

typedef struct AvlNode* AvlTree;
struct AvlNode{
	int Key;
	AvlTree Left;
	AvlTree Right;
	int Height;
};

AvlTree SingleRotateLeft(AvlTree T);
AvlTree SingleRotateRight(AvlTree T);
AvlTree	DoubleRotateLeft(AvlTree T);
AvlTree	DoubleRotateRight(AvlTree T);

int Height(AvlTree T)
{
	if(T == NULL)
		return -1;
	else return T->Height;
}

AvlTree	SingleRotateLeft(AvlTree T)		//LL 
{
	AvlTree	T1;
	
	T1 = T->Left;
	T->Left = T1->Right;
	T1->Right = T;
	
	T->Height = Height(T->Right) > Height(T->Left) ? Height(T->Right)+1 : Height(T->Left)+1;
	T1->Height = Height(T1->Right) > Height(T1->Left) ? Height(T1->Right)+1 : Height(T1->Left)+1;
	
	return T1;
}

AvlTree	DoubleRotateLeft(AvlTree T)		//LR
{
	AvlTree T1;
	
	T1 = T->Left;
	T->Left = SingleRotateRight(T1);
	T = SingleRotateLeft(T);
	
	return T;
}

AvlTree	SingleRotateRight(AvlTree T)	//RR
{
	AvlTree T1;
	
	T1 = T->Right;
	T->Right = T1->Left;
	T1->Left = T;
	
	T->Height = Height(T->Right) > Height(T->Left) ? Height(T->Right)+1 : Height(T->Left)+1;
	T1->Height = Height(T->Right) > Height(T->Left) ? Height(T->Right)+1 : Height(T->Left)+1;
	
	return T1;
}

AvlTree	DoubleRotateRight(AvlTree T)	//RL
{
	AvlTree T1;
	
	T1 = T->Right;
	T->Right = SingleRotateLeft(T1);
	T = SingleRotateRight(T);
	
	return T;
}

AvlTree Insert(int X, AvlTree T)
{
	if(T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		T->Height = 0;
		T->Left = T->Right = NULL;
		T->Key = X;
	}
	else if(X < T->Key)
	{
		T->Left = Insert(X, T->Left);
		if(Height(T->Left)-Height(T->Right) == 2)
		{
			if(X < T->Left->Key)
				T = SingleRotateLeft(T);
			else
				T = DoubleRotateLeft(T);
		}
	}
	else{
		T->Right = Insert(X, T->Right);
		if(Height(T->Right)-Height(T->Left) == 2)
		{
			if(X > T->Right->Key)
				T = SingleRotateRight(T);
			else
				T = DoubleRotateRight(T);
		}
	}
	
	T->Height = Height(T->Left) > Height(T->Right) ? Height(T->Left)+1 : Height(T->Right)+1;
	return T;
}

int main()
{
	int Nodes;
	scanf("%d", &Nodes);
	AvlTree T = NULL;
	for(int i = 0; i < Nodes; i++)
	{
		int x;
		scanf("%d", &x);
		T = Insert(x, T);
	}
	printf("%d", T->Key);
	return 0;
}

