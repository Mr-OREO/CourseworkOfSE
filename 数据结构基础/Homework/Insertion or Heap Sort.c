#include<stdio.h>

int max;
int I_index;
int H_index;

void Insertion_sort(int* array);
void BuildHeap(int* array);
void Heap_sort(int* array);
int Compare(int* ary1, int* ary2);

int main()
{
	scanf("%d", &max);
	H_index = max - 1;
	int* num1[max], num2[max], temp[max];
	for(int i = 0; i < max; i++)
	{
		scanf("%d", num1+i);
		num2[i] = num1[i];
	}
	for(int i = 0; i < max; i++)
		scanf("%d", temp+i);
	BuildHeap(num2);
	while(1)
	{
		Insertion_sort(num1);
		if(Compare(num1, temp))
		{
			printf("Insertion Sort\n");
			Insertion_sort(num1);
			printf("%d", num1[0]);
			for(int i = 1; i < max; i++)
				printf(" %d", num1[i]);
			break;
		}
		Heap_sort(num2);
		if(Compare(num2, temp))
		{
			printf("Heap Sort\n");
			Heap_sort(num2);
			printf("%d", num2[0]);
			for(int i = 1; i < max; i++)
				printf(" %d", num2[i]);
			break;
		}
	}
 }

int Compare(int* ary1, int* ary2)
{
	for(int i = 0; i < max; i++)
		if(ary1[i] != ary2[i])
			return 0;
	return 1;
}


void Insertion_sort(int* array)
{
	int val = array[I_index];
	int i = I_index;
	for(; i > 0 && array[i-1] > val; i--)
		array[i] = array[i-1];
	array[i] = val;
	I_index++;
}


void Heap_sort(int *array)
{
	int val = array[0];
	array[0] = array[H_index];
	array[H_index] = val;
	int parent = 0, child, temp;
	temp = array[0];
	H_index--;
	child = parent*2+1;
	while(child<=H_index)
	{
		if(child+1 < H_index && array[child] < array[child+1])
			child++;
		if(array[child]>temp)
			array[parent] = array[child];
		else break;
		parent = child;
		child = parent*2+1;
	}
	array[parent] = temp;
}


void BuildHeap(int * array)
{
	int i = max/2;
	int parent, child, temp;
	while(i >= 0)
	{
		parent = i;
		child = parent*2+1;
		temp = array[parent];
		while(child < max)
		{
			if(child+1 < max && array[child] < array[child+1])
				child++;
			if(array[child]>temp)
				array[parent] = array[child];
			else break;
			parent = child;
			child = parent*2+1;
		}
		array[parent] = temp;
		i--;
	}
}
