#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrtoNode;
struct Node{
    int children;
    int capacity;
    int key[4];
    int leaf;
    int layer;
    PtrtoNode parent;
    PtrtoNode son[4];
};

int cmp(const void*a,const void*b)
{
    return *(int*)a-*(int*)b;
}

int main()
{
    int input;
    scanf("%d", &input);
    PtrtoNode root = (PtrtoNode)malloc(sizeof(struct Node));
    PtrtoNode current = root, prev = NULL;
    current->capacity = 0;
    current->children = 0;
    current->layer = 1;
    current->leaf = 1;
    current->parent = NULL;
    current->son[0] = current->son[1] = current->son[2] = current->son[3] = NULL;

    if(input <= 3)
    {
        int num[3];
        for(int i = 0; i < input; i++)
        {
            int ele;
            scanf("%d", &ele);
            num[i] = ele;
        }
        qsort(num, input, sizeof(int), cmp);
        printf("[%d", num[0]);
        for(int i = 1; i < input; i++)
            printf(",%d", num[i]);
        printf("]");
        return 0;
    }

    for(int i = 0; i < input; i++)
    {
        int ele, brk = 0;
        scanf("%d", &ele);
        current = root;
        //瀹氫綅current
        while(current->leaf == 0)
        {
            int j = 0;
            while(ele >= current->key[j] && j < current->children-1)
                j++;
            current = current->son[j];
        }
        //鎻掑叆
        for(int j = 0; j < current->capacity; j++)
            if(ele == current->key[j])
            {
                printf("Key %d is duplicated\n", ele);
                brk = 1;
                break;
            }
        if(brk == 1)
            continue;
        current->key[current->capacity++] = ele;
        qsort(current->key, current->capacity, sizeof(int), cmp);
        if(current->capacity <= 3)
            continue;

        while(current->children == 4 || (current->capacity == 4 && current->leaf))
        {
            int temp;
            PtrtoNode sibling = (PtrtoNode)malloc(sizeof(struct Node));
            sibling->layer = current->layer;
            if(current->leaf)
            {
                sibling->capacity = 0;
                sibling->children = 0;
                sibling->leaf = current->leaf;
                sibling->parent = current->parent;
            
                sibling->son[0] = sibling->son[1] = sibling->son[2] = sibling->son[3] = NULL;
                sibling->key[1] = current->key[--current->capacity];
                sibling->key[0] = current->key[--current->capacity];
                sibling->capacity++;
                sibling->capacity++;
            }
            else
            {
                sibling->capacity = 0;
                sibling->children = 0;
                sibling->leaf = current->leaf;
                sibling->parent = current->parent;

                sibling->son[1] = current->son[--current->children];
                sibling->son[0] = current->son[--current->children];
                sibling->children++;
                sibling->children++;
                sibling->key[sibling->capacity++] = current->key[--current->capacity];
                temp = current->key[--current->capacity];
            }
                        
            if(current->parent == NULL)
            {
                PtrtoNode father = (PtrtoNode)malloc(sizeof(struct Node));
                //鍒濆鍖?
                root = father;
                father->capacity = 0;
                father->children = 0;
                father->parent = NULL;
                father->layer = current->layer+1;
                father->leaf = 0;
                //杩炴帴
                current->parent = father;
                sibling->parent = father;
                father->son[father->children++] = current;
                father->son[father->children++] = sibling;
                //璧嬪€?
                if(current->leaf)
                    father->key[father->capacity++] = sibling->key[0];
                else    father->key[father->capacity++] = temp;

                current = current->parent;
                continue;
            }
            else
            {
                int location = 0;
                for(int i = 0; i < current->parent->children; i++)
                {
                    if(current->parent->son[i] == current)
                        location = i;
                }
                for(int i = current->parent->children - 1; i > location; i--)
                {
                    current->parent->key[i] = current->parent->key[i-1];
                    current->parent->son[i+1] = current->parent->son[i];
                }
                current->parent->key[location] = sibling->key[0];
                current->parent->son[location+1] = sibling;
                current->parent->capacity++;
                current->parent->children++;

                current = current->parent;
                continue;
            }

            // if(current->parent->children == 4)
            // {
            //     current = current->parent;
            //     PtrtoNode father = (PtrtoNode)malloc(sizeof(struct Node));
            //     PtrtoNode sib = (PtrtoNode)malloc(sizeof(struct Node));
            //     //鍒濆鍖?
            //     root = father;
            //     father->capacity = 0;
            //     father->children = 0;
            //     father->parent = NULL;
            //     father->leaf = 0;
            //     sib->capacity = 0;
            //     sib->children = 0;
            //     sib->leaf = 0;
            //     //杩炴帴
            //     father->key[father->capacity++] = current->key[1];
            //     father->son[father->children++] = current;
            //     father->son[father->children++] = sib;
            //     sib->key[sib->capacity++] = current->key[2];
            //     sib->son[sib->children++] = current->son[2];
            //     sib->son[sib->children++] = current->son[3];
            //     current->capacity -= 2;
            //     current->children -= 2;
            // }
        }
        
        
    }
    Print(root);
    system("pause");
    return 0;
}

void Print(PtrtoNode root)
{
    PtrtoNode n[20];
    int head = 0, tail = 1, ll;
    n[0] = root;
    while(head != tail)
    {
        for(int i = 0; i < n[head]->children; i++)
            n[tail++] = n[head]->son[i];
        head++;
    }
    ll = n[0]->layer;
    for(int i = 0; i < tail; i++)
    {
        if(n[i]->layer != ll)
        {
        	printf("\n");
        	ll = n[i]->layer;
		 } 
        printf("[%d", n[i]->key[0]);
        for(int j = 1; j < n[i]->capacity; j++)
            printf(",%d", n[i]->key[j]);
        printf("]");
    }
    printf("\n");
    return;
}
