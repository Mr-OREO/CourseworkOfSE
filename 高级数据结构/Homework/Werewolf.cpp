#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
using namespace std;

int N, M, L, lies, lies2, Mlies, wolves, word[101], cnt, wolf[101];
vector<int> record[5], relation[101];
bool Flag = 0;

void DFS(int left);

int main()
{
    cin >> N >> M >> L;
    for(int i = 1; i <= N; i++)
    {
        cin >> word[i];
        relation[abs(word[i])].push_back((word[i]>0?1:-1)*i);
    }
    DFS(N);
    if(!Flag)
        cout << "No Solution";
    else
    {
        vector<int> temp;
        temp.push_back(0);
        for(int i = 0; i < cnt; i++)
        {
            sort(record[i].begin(), record[i].end());
            reverse(record[i].begin(), record[i].end());
            if(temp < record[i])
                temp = record[i];
        }
        cout << temp[0];
        for(int i = 1; i<temp.size(); i++)
            cout <<" "<<temp[i];
    }

    return 0;
}

void DFS(int left)
{
    if(lies > L)
        return;
    if(wolves == M)
    {
        lies2 = Mlies = 0;
        for(int i = 1; i <= N; i++)
        {
            if((word[i]<0 && !wolf[abs(word[i])]) || (word[i]>0 && wolf[abs(word[i])]))
            {
                if(wolf[i]) Mlies++;
                lies2++;
            }
        }

        if(lies2 == L && Mlies < M && Mlies>0)
        {
            Flag = 1;
            for(int i = 1; i <= N; i++)
            {
                if(wolf[i])
                    record[cnt].push_back(i);
            }
            cnt++;
            return;
        }
    }

    for(int i = left; i > 0; i--)
    {
        if(left + wolves < M) return;
        wolf[i] = 1;
        wolves++;
        for(int j = 0; j < relation[i].size(); j++)
            lies += relation[i][j] > 0 ? 1 : 0;
        DFS(i-1);
        wolf[i] = 0;
        wolves--;
        for(int j = 0; j < relation[i].size(); j++)
            lies += relation[i][j] > 0 ? -1 : 0;
    }
}