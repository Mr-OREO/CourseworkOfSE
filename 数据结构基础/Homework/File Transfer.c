#include<stdio.h>
void Union(int* P, int a, int b);
void Initial(int* P, int size);
int Find(int* P, int a);
int main()
{
	int N, in1, in2, i;
	int component = 0;
	char input;
	scanf("%d", &N);
	int p[N+1];
	Initial(p, N+1);
	while(1)
	{
		scanf("%c", &input);
		if(input == 'S')
			break;
		else if(input == 'I')
		{
			scanf("%d%d", &in1, &in2);
			Union(p, in1, in2);
		}
		else if(input == 'C')
		{
			scanf("%d%d", &in1, &in2);
			if(Find(p, in1) != Find(p, in2))
				printf("no\n");
			else printf("yes\n");
		}
	}
	for(i = 1; i <= N; i++)
		if(p[i] < 0)
			component++;
	if(component == 1)
		printf("The network is connected.\n");
	else printf("There are %d components.\n", component);
	return 0;
 } 
 
void Initial(int* P, int size)
{
	int i = 1;
	for( ; i <= size; i++)
		P[i] = -1;
}

int Find(int* P, int a)
{
	int root;
	if(P[a] < 0)
		return a;
	else return root = Find(P, P[a]);
}

void Union(int* P, int a, int b)
{
	int root1 = Find(P, a);
	int root2 = Find(P, b);
	int rank1 = P[root1];
	int rank2 = P[root2];
	if(rank1 < rank2)
	{
		P[root2] = root1;
		P[root1] += rank2;
	}
	else{
		P[root1] = root2;
		P[root2] += rank1;
	}
}

