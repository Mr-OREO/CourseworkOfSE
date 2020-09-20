#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INFINITY 100000

char satel[1000][4];
int Sindex;				//point to the blank after the last element
int capacity[1000][1000];
int flow[500];
int pre[500];
int queue[100];
int front, rear;

int Min(int num1, int num2)
{
	return num1<num2?num1:num2;
}

int Find(char* s)
{
	for(int i = 0; i < Sindex; i++)
		if(!strcmp(satel[i], s))
			return i;
	strcpy(satel[Sindex++], s);
	return Sindex-1;
}

int BFS(int src, int des)
{
	memset(pre, -1, sizeof(pre));
	front = rear = 0;
	pre[src] = 0;
	flow[src] = INFINITY;
	queue[rear] = src;
	while(front <= rear)
	{
		int index = queue[front++];
		if(index == des)	break;
		for(int i = 0; i < Sindex; i++)
		{
			if(i != src && capacity[index][i]>0 && pre[i]==-1)
			{
				pre[i] = index;
				flow[i] = Min(capacity[index][i], flow[index]);
				queue[++rear] = i;
			}
		}
	}
	if(pre[des] == -1)	return -1;
	else return flow[des];
}

int Maxflow(int src, int des)
{
	int addition = 0;
	int maxflow = 0;
	while((addition = BFS(src, des)) != -1)
	{
		int k = des;
		front = rear = 0;
		while(k != src)
		{
			capacity[pre[k]][k] -= addition;
			capacity[k][pre[k]] += addition;
			k = pre[k];
		}
		maxflow += addition;
	}
	return maxflow;
}

int main()
{
	char source[4], destination[4], from[4], to[4];
	int weight = 0, Ne;
	scanf("%s%s%d", source, destination, &Ne);
	strcpy(satel[Sindex++], source);
	for(int i = 0; i < Ne; i++)
	{
		scanf("%s%s%d", from, to, &weight);
		capacity[Find(from)][Find(to)] = weight;
	}
	printf("%d", Maxflow(Find(source), Find(destination)));
	return 0;
}

