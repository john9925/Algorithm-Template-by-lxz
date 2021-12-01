//2020/8/18
//有奇数环（边数为奇数）一定不是二分图
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
vector<int>g[N];
int n,m,color[N];
bool dfs(int u,int c)
{
    color[u]=c;
    for(auto i:g[u])
    {
        if(!color[i])
        {
            if(!dfs(i,3-c))return 0;
        }
        else if(color[i]==c) return 0;
    }
    return 1;
}
int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    bool flag= 1;
    for(int i=1;i<=n;i++)//这个图可能有几个块
    {
        if(!color[i])
        {
            if(!dfs(i,1))
            {
                flag=0;
                break;
            }
        }
    }
    if(flag)puts("Yes");
    else puts("No");
    return 0;

}
