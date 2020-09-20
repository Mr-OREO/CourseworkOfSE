#include<stdio.h>
#include<stdlib.h>

int Inorder[1001], CBST[1001];
int Position = 1, Size;

void Bsort(int *array)
{
	int i = 1, j = 1;
	int temp;
	for( ; i < Size; i++)
	{
		for( j = 1; j < Size - i + 1; j++)
		{
			if(array[j] > array[j+1])
			{
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

void InTraverse(int index, int *array2)
{
	if( 2*index <= Size)
		InTraverse(2*index, array2);
	array2[index] = Inorder[Position++];
	if( 2*index + 1 <= Size)
		InTraverse(2*index +1, array2);
}

int main()
{
	int i;
	scanf("%d", &Size);
	for( i = 1; i <= Size; i++)
		scanf("%d", Inorder + i);
	Size = --i;
	Bsort( Inorder );
	InTraverse( 1, CBST);
	printf("%d", CBST[1]);
	for( i = 2; i<=Size; i++)
		printf(" %d", CBST[i]);
	return 0; 
}



