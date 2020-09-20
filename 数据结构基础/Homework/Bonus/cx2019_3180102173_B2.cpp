/* Author: Wang ZiTeng;  ID: 3180102173;  No.02 */ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

#define	INF	0x7fffffff

int Graph[502][502];
int mincost[502];
int N, M;

//int cmp(const void* a, const void* b)
//{
//	return *(int*)b - *(int*)a;
//}

void Input()
{
	int c1, c2, cost, status;
	for(int i = 0; i < M; i++)
	{
		scanf("%d%d%d%d", &c1, &c2, &cost, &status);
		if(!status)
		{
			Graph[c1][c2] = cost;
			Graph[c2][c1] = cost;
		}
		else{
			Graph[c1][c2] = 0;
			Graph[c2][c1] = 0;
		}
	}
}

void Prim(int del)
{
	//Initialise temp with deletion
	int	temp[N+1][N+1];
	for(int i = 1; i <= N; i++)
		memcpy(temp[i], Graph[i], (N+1) * sizeof(int));
	for(int i = 1; i <= N; i++)
		temp[del][i] = INF;
	for(int i = 1; i <= N; i++)
		temp[i][del] = INF;
	//start point
	int min = INF, min_i = -1, Cost = 0;
	if(del == 1)
		min_i = 2;
	else min_i = 1;
	int weight[N+1], visited[N+1];
	for(int i = 1; i <= N; i++)
	{
		weight[i] = INF;
		visited[i] = 0;
	}
	weight[min_i] = 0;
	visited[min_i] = 1;
	//Prim Algorithm
	for(int i = 1; i < N-1; i++)
	{
		//update the weight
		for(int j = 1; j <= N; j++)
			if(!visited[j] && temp[min_i][j] < weight[j])
				weight[j] = temp[min_i][j];
		//find the min
		min = INF;
		for(int j = 1; j <= N; j++)
			if(!visited[j] && weight[j] < min)
			{
				min = weight[j];
				min_i = j;
			}
		//if(min == INF)	break;
		Cost += min;
		if(min == INF)
		{
			Cost = INF;
			break;
		 } 
		visited[min_i] = 1;
		weight[min_i] = 0;
	 }
	 mincost[del] = Cost;
}

int main()
{
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			Graph[i][j] = INF;
	Input();
	for(int i = 1; i <= N; i++)
		Prim(i);
//	qsort(mincost+1, N, sizeof(int), cmp);
	int max = -1;
	for(int i = 1; i <= N; i++)
		if(mincost[i] > max)
			max = mincost[i];
	int time = 1;
	if(max == 0)
	{
		printf("0");
		return 0;
	}
	for(int i = 1; i <= N; i++)
		if(mincost[i] == max && time == 1)
		{
			printf("%d", i);
			time++;
		}
		else if(mincost[i] == max)
			printf(" %d", i);
	return 0;
}

