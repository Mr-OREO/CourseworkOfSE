#include<stdio.h>

int max;
//int I_index;
//int H_index;

int Insertion_sort(int* array, int* com);
void BuildHeap(int* array);
void Heap_sort(int* array, int *com);
int Compare(int* ary1, int* ary2);

int main()
{
	scanf("%d", &max);
//	H_index = max - 1;
	int* num1[max], num2[max], temp[max];
	for(int i = 0; i < max; i++)
	{
		scanf("%d", num1+i);
		num2[i] = num1[i];
	}
	for(int i = 0; i < max; i++)
		scanf("%d", temp+i);
	BuildHeap(num2);
	if(Insertion_sort(num1, temp))
		return 0;
	Heap_sort(num2, temp);
	return 0;
 }

int Compare(int* ary1, int* ary2)
{
	for(int i = 0; i < max; i++)
		if(ary1[i] != ary2[i])
			return 0;
	return 1;
}


//int Insertion_sort(int* array, int* com)
//{
//	int val, jump = 0;
//	int j = 1, i;
//	if(max == 1)
//	{
//		printf("Insertion Sort\n");
//		printf("%d", array[0]);
//		return 1;
//	}
//	for( ; j < max; j++)
//	{
//		if(array[j]>array[j-1])	
//			continue;
//		if(Compare(array, com))
//		{
//			printf("Insertion Sort\n");
//			jump = 1;
//		}
//		val = array[j];
//		for(i = j; i > 0 && array[i-1] > val; i--)
//			array[i] = array[i-1];
//		array[i] = val;
//		if(jump)
//		{
//			printf("%d", array[0]);
//			for(int i = 1; i < max; i++)
//				printf(" %d", array[i]);
//			printf("\n");
//			return 1;
//		}
//	}
//	return 0;
//}

int Insertion_sort(int *array,int* com)
{
	int flag=0;

	for(int i=0; i<max; i++)
	{
		if(array[i]<array[i-1])
		{
			int tmp=array[i];
			int j;
			for(j=i; j>0; j--)
			{
				if(array[j-1]>tmp)
					array[j]=array[j-1];
				else break;
			}
			array[j]=tmp;
			if(flag)break;
		}
		flag=Compare(array, com);
	}
	if(flag)
	{
		printf("Insertion Sort\n");
		for(int i=0; i<max; i++)
		{
			if(i)printf(" ");
			printf("%d",array[i]);
		}
		printf("\n");
		return 1;
	}
	return 0;
}


void Heap_sort(int *array, int *com)
{
	int index = max - 1;
	int val, jump = 0;
	for( ; index > 0; index--)
	{
		if(Compare(array, com))
		{
			printf("Heap Sort\n");
			jump = 1;
		}
		val = array[0];
		array[0] = array[index];
		array[index] = val;
		int parent = 0, child, tmp = array[0];
		child = parent*2+1;
		while(child<index)
		{
			if(child+1 < index && array[child] < array[child+1])
				child++;
			if(array[child]>tmp)
				array[parent] = array[child];
			else break;
			parent = child;
			child = parent*2+1;
		}
		array[parent] = tmp;
		if(jump)
		{
			printf("%d", array[0]);
			for(int i = 1; i < max; i++)
				printf(" %d", array[i]);
			return;
		}
	}
}


void BuildHeap(int* array)
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
