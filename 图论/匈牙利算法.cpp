#include<bits/stdc++.h>
using namespace std;
const int N=505;
vector<int>g[N];
int n1,n2,m,match[N];//match 右边女孩匹配的左边男孩
bool st[N];//每次循环右边点是否被选，
bool find(int x)
{
    for(auto i:g[x])
    {
        if(!st[i])
        {
            st[i]=1;
            if(match[i]==0||find(match[i]))
            {
                match[i]=x;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    cin>>n1>>n2>>m;
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
    }
    int res=0;
    for(int i=1;i<=n1;i++)
    {
        memset(st,0,sizeof(st));
        if(find(i))res++;
    }
    cout<<res;
    return 0;
}