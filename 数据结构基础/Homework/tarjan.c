int stk = -1;
int cnt = 1;
int stack[10];
int visited[10];
int DFN[10];
int LOW[10];
int color[10];

int min(int a, int b)
{
	return	a<b? a: b;
}

void Tarjan(Graph G, vertex v)
{
	stack[++stk] = v;
	DFN[v] = LOW[v] = cnt++;
	visit[v] = 0;
	PtrToVNode	temp = G->Array[v];
	while(temp)
	{
		int u = temp->Next;
		if(!visited[u])
		{
			Tarjan(G, u);
			LOW[v] = min(LOW[v], LOW[u]);
		}
		else if(!color[u])
		{
			LOW[v] = min(LOW[v], DFN[u]);
		}
		temp = temp->Next;
	}
	if(DFN[v] == LOW[v])
	{
		int ver = stack[stk--];
		while(ver != v)
		{
			printf("%d ", ver);
			ver = stack[stk--];
			color[ver] = 1;
		}
		printf("\n");
	}
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) )
{
	for(int i = 0; i < G->NumOfVertices; i++)
		if(!visited[i])
			Tarjan(G, i);
}
