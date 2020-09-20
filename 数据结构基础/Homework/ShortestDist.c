void ShortestDist( MGraph Graph, int dist[], Vertex S )
{
	int nv = Graph->Nv;
	int visited[nv];
	for(int i = 0; i < nv; i++)
	{
		dist[i] = INFINITY;
		visited[i] = 0;
	}
	dist[S] = 0;
	visited[S] = 1;
	for(int i = 0; i < nv-1; i++)
	{
		for(int j = 0; j < nv; j++)
			if(!visited[j]&&dist[j] > dist[S] + Graph->G[S][j])
				dist[j] = dist[S] + Graph->G[S][j];
		int min = INFINITY, min_i = -1;
		for(int j = 0; j < nv; j++)
			if(!visited[j]&&dist[j]<min)
			{
				min = dist[j];
				min_i = j;
			}
		if(min_i == -1)	break;
		S = min_i;
		visited[S] = 1;
	}
	for(int i = 0; i < nv; i++)
		if(visited[i] == 0)
			dist[i] = -1;
}
