#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here */

bool IsTopSeq( LGraph Graph, Vertex Seq[] )
{
	int i = 0, j = 0;
	AdjList GG;
	PtrToAdjVNode current = NULL;
	for( ; i < Graph->Nv ; i++)
	{
		for(j = 0; j < Graph->Nv; j++)
		{
			current = Graph->G[j].FirstEdge;
			while(current)
			{
				if(current->AdjV == Seq[i])
					return false;
				current = current->Next;
			}
		}
		GG[Seq[i]-1].FirstEdge = Graph->G[Seq[i]-1].FirstEdge;
		Graph->G[Seq[i]-1].FirstEdge = NULL;
	}
	for(i = 0; i < Graph->Nv; i++)
		Graph->G[Seq[i]-1].FirstEdge = GG[Seq[i]-1].FirstEdge;
	return true;
}



LGraph ReadG() /* details omitted */
{
    LGraph G = (LGraph)malloc(sizeof(struct GNode));
    G->Ne = G->Nv = 0;
    scanf("%d%d", &G->Nv, &G->Ne);
    for (int i = 0; i < G->Nv; ++i)
    {
        G->G[i].FirstEdge = NULL;
        //G->G[i].FirstEdge->Next = NULL;
    }
    for (int i = 0; i < G->Ne; ++i)
    {
        Vertex from, to;
        scanf("%d%d", &from, &to);

        if (G->G[from - 1].FirstEdge == NULL)
        {
            G->G[from - 1].FirstEdge = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
            G->G[from - 1].FirstEdge->AdjV = to;
            G->G[from - 1].FirstEdge->Next = NULL;
        }
        else
        {
            PtrToAdjVNode p = G->G[from - 1].FirstEdge;
            while (p->Next != NULL)
                p = p->Next;
            p->Next = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
            p = p->Next;
            p->AdjV = to;
            p->Next = NULL;
        }
    }
    return G;
}


