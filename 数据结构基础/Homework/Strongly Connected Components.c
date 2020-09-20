#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */

PtrToVNode insert(PtrToVNode p,int x)  

{  

    p->Next=(PtrToVNode)malloc(sizeof(struct VNode));  

    p=p->Next;  

    p->Vert=x;  

    p->Next=NULL;  

    return p;  

}  

 

Graph ReadG()

{

	int i,j,m,n,x,y;  

    scanf("%d%d",&m,&n);   

    Graph p=(Graph)malloc(sizeof(struct GNode));  

    PtrToVNode *rear=(PtrToVNode*)malloc(m*sizeof(struct VNode));  

    p->Array=(PtrToVNode*)malloc(m*sizeof(struct VNode));  

    p->NumOfVertices=m;  

    p->NumOfEdges=n;  

    for(i=0;i<m;i++){  

        rear[i]=p->Array[i]=(PtrToVNode)malloc(sizeof(struct VNode));  

        p->Array[i]->Next=NULL;  

    }  

    for(i=0;i<n;i++){  

        scanf("%d%d",&x,&y);  

        rear[x]=insert(rear[x],y);  

    }  

    for(i=0;i<m;i++){  

        PtrToVNode tmp=p->Array[i];  

        p->Array[i]=p->Array[i]->Next;  

        tmp->Next=NULL;  

        free(tmp);  

    }   

    return p; 

}

int stk = -1;
int cnt = 1;
int stack[10];
int DFN[10];
int LOW[10];
int vst[10];
int instack[10];

int min(int a, int b)
{
	if(a < b)	return a;
	else return b;
}

void Tarjan(int i, Graph G)
{
	DFN[i] = LOW[i] = cnt++;
	stack[++stk] = i;
	vst[i] = 1;
	PtrToVNode temp = G->Array[i];
	while(temp)
	{
		int v = temp->Vert;
		if(!DFN[v])
		{
			Tarjan( v, G);
			LOW[i] = min(LOW[i], LOW[v]);
		}
		else if(instack[v] == 0)
			LOW[i] = min(LOW[i], DFN[v]);
		temp = temp->Next;
	}
	if(DFN[i] == LOW[i])
	{
		int top;
		while(top != i)
		{
			top = stack[stk--];
			printf("%d ", top);
			instack[top] = 1;
		}
		printf("\n");
	}
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) )
{
	memset(DFN, 0, sizeof(DFN));
	memset(LOW, 0, sizeof(LOW));
	memset(vst, 0, sizeof(vst));
	memset(instack, 0, sizeof(instack));
	for(int j = 0; j < G->NumOfVertices; j++)
	{
		if(vst[j] == 0)
			Tarjan(j, G);
	}
}





