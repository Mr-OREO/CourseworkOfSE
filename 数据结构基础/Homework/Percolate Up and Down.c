#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;
    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        H->Elements;
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

/* Your function will be put here */
PriorityQueue Initialize( int MaxElements )
{
	PriorityQueue H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	H->Elements = (ElementType*)malloc((MaxElements+1)*sizeof(ElementType)); 
	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = MinData;
	return H;
}

void PercolateUp( int p, PriorityQueue H )
{
	ElementType Temp = H->Elements[p];
	for(; H->Elements[p/2] > Temp; p /=2)
	{
		H->Elements[p] = H->Elements[p/2];
	}
	H->Elements[p] = Temp;
}

void PercolateDown( int p, PriorityQueue H )
{
	ElementType Temp = H->Elements[p];
	int parent = p, child;
	for(; parent*2 <= H->Size; parent = child)
	{
		child = parent*2;
		if(child < H->Size && H->Elements[child] > H->Elements[child+1])
			child++;
		if(Temp > H->Elements[child])
			H->Elements[parent] = H->Elements[child];
		else break;
	}
	H->Elements[parent] = Temp;
}







