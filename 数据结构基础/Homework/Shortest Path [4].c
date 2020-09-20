
#include <stdio.h>

#include <stdlib.h>

 

 

 

 

#define INFINITY 1000000

#define MaxVertexNum 10  /* maximum number of vertices */

typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */

typedef int WeightType;

typedef struct GNode *PtrToGNode;

struct GNode{

    int Nv;

    int Ne;

    WeightType G[MaxVertexNum][MaxVertexNum];

};

typedef PtrToGNode MGraph;

 

 

MGraph ReadG(); /* details omitted */

 

 

void ShortestDist( MGraph Graph, int dist[], int count[], Vertex S );

 

 

int main()

{

    int dist[MaxVertexNum], path[MaxVertexNum];

    Vertex S, V;

    MGraph G = ReadG();

 

 

    scanf("%d", &S);

    ShortestDist( G, dist, path, S );

 

 

    for ( V=0; V<G->Nv; V++ )

        printf("%d ", dist[V]);

    printf("\n");

    for ( V=0; V<G->Nv; V++ )

        printf("%d ", path[V]);

    printf("\n");

 

 

    return 0;

}


MGraph ReadG()

{

	MGraph P;

	int i,j,k;

	P=(MGraph)malloc(sizeof(struct GNode));

	scanf("%d%d",&P->Nv,&P->Ne);

	for( j=0;j<MaxVertexNum;j++){

		for( k=0;k<MaxVertexNum;k++){

			P->G[j][k]=INFINITY;

		}

	}

	for( i=0;i<P->Ne;i++){

		int m,n;

		scanf("%d%d",&m,&n);

		scanf("%d",&P->G[m][n]);

	}

	

	return P;

}

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S )
{
	int nv = Graph->Nv, ne = Graph->Ne;
	int edge[nv], Known[nv];
	int i, j;
	for(i = 0; i < nv; i++)
	{
		dist[i] = INFINITY;
		path[i] = -1;
	}
	memset(edge, 0, nv * sizeof(int));
	memset(Known, 0, nv * sizeof(int));
	dist[S] = 0;
	for(i = 0; i < nv; i++)
	{
		for(j = 0; j < nv; j++)							//更新S附近的节点
			if(Graph->G[S][j] != INFINITY && S != j)
				if(dist[j] == Graph->G[S][j] + dist[S] && edge[j] > edge[S] + 1)
				{
					edge[j] = edge[S] + 1;
					path[j] = S;
				}
				else if(dist[j] > Graph->G[S][j] + dist[S])
				{
					dist[j] = Graph->G[S][j] + dist[S];
					path[j] = S;
					edge[j] = edge[S] + 1;
				}
		int min = INFINITY;
		for(j = 0; j < nv; j++)							//选取新的S
		{
			if(!Known[j] && dist[j] < min)
			{
				min = dist[j];
				S = j;
			}
		}
		if(min == INFINITY)
			break;
		Known[S] = 1;
	}
	for(i = 0; i < nv; i++)
		if(dist[i] == INFINITY)
			dist[i] = -1;
 }
