#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */

void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
	int l_min, r_min, l_max, r_max;
	int top = 0;
	if(N < length)
		return;
	for(l_min = 0; l_min < N; l_min = r_max)
	{
		l_max = l_min + length;
		r_min = l_max;
		r_max = r_min + length;
		if(l_max >= N)
		{
			for(int i = l_min; i < N; i++)
				sorted[top++] = list[i];
			return;
		}
		while(l_min < l_max && r_min < r_max && r_min < N)
			if(list[l_min] < list[r_min])
				sorted[top++] = list[l_min++];
			else sorted[top++] = list[r_min++];
		if(l_min < l_max)
			while(l_min < l_max)
				sorted[top++] = list[l_min++];
		else if(r_min < r_max && r_min < N)
			while(r_min < r_max && r_min < N)
				sorted[top++] = list[r_min++];
	}
}
