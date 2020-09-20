#include<stdio.h>

int start = 1;

int Find(int* arr, int N, int find)
{
	for(int i = 0; i < N; i++)
		if(arr[i] == find)	return i;
}

int Findf(int* arr, int N)
{
	for(int i = start; i < N; i++)
		if(arr[i] != i)	return i;
	return 0;
}

void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int finish(int* arr, int* std, int N)
{
	for(int i = 0; i < N; i++)
		if(arr[i] != std[i])	return 0;
	return 1;
} 

int main()
{
	int index0, cnt = 0, index, N;
	int i, j;
	scanf("%d", &N);
	int num[N];
	int correct[N];
	int std[N];
	for(i = 0; i < N; i++)
		std[i] = i;
	memset(correct,0,sizeof(correct));
	for(i = 0; i < N; i++)
		scanf("%d", num+i);
	int tmp;
	start = Findf(num, N);
	while(start)
	{
//		if(finish(num, std, N))	break;
		if(num[0]==0){
			num[0] = num[start];
			num[start] = 0;
			cnt++;
		}
		while(num[0]!=0){
			tmp = num[0];
			num[0] = num[tmp];
			num[tmp] = tmp;
			cnt++;
		}
		start = Findf(num, N);
		
//		index0 = Find(num, N, 0);
//		if(index0 == 0)
//			index = Findf(num, N);
//		else index = Find(num, N, index0);
//		Swap(num+index0, num+index);
//		cnt++;
	}
	printf("%d", cnt);
	return 0;
}



