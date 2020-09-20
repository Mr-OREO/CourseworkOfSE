#include<stdio.h>
int tree[31][2], n, gen, k=0, Layer;
int in[31], post[31], result[31][10];

typedef struct TreeNode* Tree;
struct TreeNode{
	int layer;
	int local;
	Tree next;
};

void dfs(int *a, int inL, int inR, int poL, int poR);

void dfs(int *a, int inL, int inR, int poL, int poR)
{
	int i = 0;
	if(inL > inR)	return;
	*a = poR;
	while(in[i] != post[poR])	i++;
	dfs(&tree[*a][0], inL, i-1, poL, poL + (i-inL) - 1);
	dfs(&tree[*a][1], i+1, inR, poL + (i - inL), poR - 1);
}

void bfs(int location)
{
	Tree front = NULL, rear = NULL, prev, current = (Tree)malloc(sizeof(struct TreeNode));
	front = rear = current;
	current->next = NULL;
	current->layer = 0;
	prev = current;
	current = (Tree)malloc(sizeof(struct TreeNode));
	current->layer = 1;
	Layer = 1;
	front = current;
	prev->next = current;
	current->next = NULL;
	current->local = location; 
	prev = current;
	while(front!=rear)
	{
		int temp = rear->next->layer;
		Tree discard = rear->next;
		if(Layer < temp)
		{
			Layer++;
			k=0;
		}
		result[discard->layer][k++] = post[discard->local];
		if(rear->next == front )
		{
			front = rear;
			rear->next = NULL;
		}
		else{
			rear->next = rear->next->next;
		}
		if(tree[discard->local][0])
		{
			current = (Tree)malloc(sizeof(struct TreeNode));
			prev->next = current;
			current->layer = temp+1;
			current->next = NULL;
			current->local = tree[discard->local][0];
			prev = current;
		}
		if(tree[discard->local][1])
		{
			current = (Tree)malloc(sizeof(struct TreeNode));
			prev->next = current;
			current->layer = temp+1;
			current->next = NULL;
			current->local = tree[discard->local][1];
			prev = current;
		}
	}
}


int main()
{
	int i = 1;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)	scanf("%d", &in[i]);
	for(i = 1; i <= n; i++)	scanf("%d", &post[i]);
	dfs(&gen, 1, n, 1, n);
	bfs(n);
	printf("%d", post[n]);
	for(i = 2; i <= Layer; i++)
	{
		if(i%2 == 1)
		{
			for(int j=0;result[i][j]!=0;j++)
			{
				printf(" %d", result[i][j]);
			}
		}
		else{
			int j = 0;
			while(result[i][j]!=0)	j++;
			j--;
			for(;j>=0;j--)
			{
				printf(" %d", result[i][j]);
			}
		}
	}
	return 0;
}
