#include<stdio.h>

int isEnd(int* arr, int n)
{
	for(int i = 0; i < n; i++)
		if(arr[i] == 0)
			return 0;
	return 1;
}

int main()
{
	int N, index = 0;
	scanf("%d", &N);
	int isin[N], hash[N], seq[N];
	memset(isin, 0, N * sizeof(int));
	memset(seq, 0, N * sizeof(int));
	int ok = 1;
//read in and initialise hashtable
	for(int i = 0; i < N; i++)
	{
		scanf("%d", hash+i);
		if(hash[i] < 0)
			isin[i] = 1;
	}
//
	while(!isEnd(isin, N))
	{
		int min, i = 0, j = 0, min_i = 1000;
		min = 100000000;
		// select min
		for(i = 0; i< N; i++)
		{
			ok = 1;
			if(isin[i])
				continue;
			if(hash[i] < min)
			{
				int crt = hash[i] % N;
				if(crt == i){
					min = hash[i];
					min_i = i;
				}
				else{
					for(j = crt; j % N != i; j++)
						if(!isin[j % N])	ok = 0;
					if(ok){
						min = hash[i];
						min_i = i;
					}
				}
			}
		}
		isin[min_i] = 1;
		seq[index++] = min;
	}
	for(int i = 0; i < index; i++)
		if(i == 0)
			printf("%d", seq[0]);
		else printf(" %d", seq[i]);
	return 0;
}
