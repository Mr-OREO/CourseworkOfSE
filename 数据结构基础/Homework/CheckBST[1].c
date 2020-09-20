#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
struct TNode{
    int Key;
    BinTree Left;
    BinTree Right;
};

BinTree BuildTree(); /* details omitted */
int CheckBST ( BinTree T, int K );

int main()
{
    BinTree T;
    int K, out;

    T = BuildTree();
    scanf("%d", &K);
    out = CheckBST(T, K);
    if ( out < 0 )
        printf("No.  Height = %d\n", -out);
    else
        printf("Yes.  Key = %d\n", out);

    return 0;
}
/* 你的代码将被嵌在这里 */


void InBST( BinTree T);
int GetTreeHeight(BinTree T);
int num[30], i;
int CheckBST ( BinTree T, int K )
{
	int condition = 1;
	InBST(T);
	for(int j = 0;j < i-1;j++)
		if(num[j] > num[j+1])
		{
			condition = 0;
			break;
		}
	if(condition == 1)
	{
		BinTree current = T;
		int j = i;
		j -= K;
		return num[j];
	}
	else 
	{
		return -1 * GetTreeHeight(T);
	}
}

void InBST( BinTree T)
{
	if(T == NULL)
		return;
	InBST(T->Left);
	num[i++] = T->Key;
	InBST(T->Right);
	return;
}

int GetTreeHeight(BinTree T)
{
	if(T == NULL)
		return 0;
	int LeftSubHeight = GetTreeHeight(T->Left);
	int RightSubHeight = GetTreeHeight(T->Right);
	return LeftSubHeight>=RightSubHeight ? LeftSubHeight+1 :RightSubHeight+1;
}

