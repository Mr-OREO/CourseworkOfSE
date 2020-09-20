/* Author: Wang ZiTeng;  ID: 3180102173;  No.01 */ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct TreeNode{
	int weight;
	int childnum;
	int sum;
	int parent;
};
struct TreeNode Tree[101];
int Edge[101][101];

int cmp(const void* a, const void* b)
{
	return Tree[*(int*)b].weight - Tree[*(int*)a].weight;
}

int array[101][101];
int	flag[101];
int line;

void RecordNode(int index)
{
	int current = index;
	int i = 0, j = 0, arr[101];
	while(current>=0)
	{
		arr[i++] = Tree[current].weight;
		current = Tree[current].parent;
	}
	while(i > 0)
	{
		array[line][j++] = arr[--i];
	}
	array[line][j] = -1;
	line++;
}

void Print()
{
	int max[101], max_i;
	for(int j = 0; j < line; j++)
	{
		for(int i = 0; i < line; i++)
		{
			if(!flag[i])
			{
				memcpy(max, array[i], 101 * sizeof(int));
				max_i = i;
				break;
			}
		}
		for(int i = 0;i < line; i++)
		{
			int k = 0;
			if(flag[i])	continue;
			while(array[i][k] > 0 && max[k] > 0)
			{
				if(array[i][k] > max[k])
				{
					memcpy(max, array[i], 101*sizeof(int));
					max_i = i;
					break;
				}
				else if(max[k] > array[i][k])
					break;
				k++;
			}
		}
		flag[max_i] = 1;
		printf("%d", max[0]);
		for(int i = 1; max[i] > 0; i++)
			printf(" %d", max[i]);
		printf("\n");
	}
}

void DFS(int start, int s)
{
	int next;
	for(int i = 0; i < Tree[start].childnum; i++)
	{
		next = Edge[start][i];
		Tree[next].sum = Tree[start].sum + Tree[next].weight;
		if(Tree[next].sum == s)
			if(Tree[next].childnum == 0)	RecordNode(next);
			else	continue;
		else if(Tree[next].sum < s)
			DFS(next,s);
		else continue;
	}
}

int main()
{
	int N, M, S;
	scanf("%d%d%d", &N, &M, &S);
	Tree[0].parent = -1;
	for(int i = 0; i< N; i++)
		scanf("%d", &Tree[i].weight);
	Tree[0].sum = Tree[0].weight;
	for(int i = 0; i< M; i++)
	{
		int index;
		scanf("%d", &index);
		scanf("%d", &Tree[index].childnum);
		for(int j = 0; j < Tree[index].childnum; j++)
		{
			scanf("%d", &Edge[index][j]);
			Tree[Edge[index][j]].parent = index;
		}
		qsort(Edge[index], Tree[index].childnum, sizeof(int), cmp);
	}
	if(M == 0)
	{
		if(Tree[0].weight == S)	printf("%d", Tree[0].weight);
		return 0;
	}
	DFS(0, S);
	Print();
	return 0;
}

