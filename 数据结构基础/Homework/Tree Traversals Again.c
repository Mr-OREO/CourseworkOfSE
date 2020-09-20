#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode* Tree;
struct TreeNode{
	int Element;
	Tree Left;
	Tree Right;
	Tree Prev;
	int Pop;
};
int N;

void Postorder(Tree head);

int main()
{
	int i = 1, state = 0, element;	//state: (previous) Push:0, Pop:1
	char operation[10];
	Tree head = NULL, current, prev = NULL;
	scanf("%d", &N);
	for(i = 1; i<=2*N; i++)		//create tree
	{
		scanf("%s", operation);
		if(operation[0] == 'P' && operation[1] == 'u')	//add
		{
			scanf(" %d", &element); 
			if(prev == NULL)	//head Node
			{
				head = (Tree)malloc(sizeof(struct TreeNode));
				head->Left = NULL;
				head->Right = NULL;
				head->Prev = NULL;
				head->Element = element;
				head->Pop = 0;
				prev = head;
				continue;
			}
			if(state == 0)		//at left
			{
				current = (Tree)malloc(sizeof(struct TreeNode));
				current->Prev = prev;
				prev->Left = current;
				current->Element = element;
				current->Left = current->Right = NULL;
				current->Pop = 0; 
				prev = current;
			}
			else if(state == 1)		//at right
			{
//				prev = prev->Left;
				current = (Tree)malloc(sizeof(struct TreeNode));
				current->Prev = prev;
				prev->Right = current;
				current->Element = element;
				current->Left = current->Right = NULL;
				current->Pop = 0;
				prev = current;
			}
			state = 0;
		}
		else
		{
			while(prev->Pop == 1)
				prev = prev->Prev;
			prev->Pop = 1;
			state = 1;
		}
	}
	Postorder(head);
	return 0;
}

void Postorder(Tree Node)
{
	if(Node == NULL)
		return;
	Postorder(Node->Left);
	Postorder(Node->Right);
	printf("%d", Node->Element);
	if(N-- > 1)
		printf(" ");
}




