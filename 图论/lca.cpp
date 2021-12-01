#include<bits/stdc++.h>
using namespace std;
const int N=4*1e4+10;
int f[N][16],depth[N],n,root,q[N];
vector<int>g[N];
void bfs(int root)
{
    memset(depth,0x3f,sizeof depth);
    int hh=0,tt=0;
    q[hh]=root;
    depth[0]=0,depth[root]=1;//depth[0]=0,设置为哨兵。当f跳出去了，就会跳到0。
    while(hh<=tt)
    {
        int u=q[hh++];
        for(auto i:g[u])
        {
            if(depth[i]>depth[u]+1)
            {
                depth[i]=depth[u]+1;
                q[++tt]=i;
                f[i][0]=u;//i是u的子节点，i往上跳一步就到u
                for(int k=1;k<=15;k++)
                    f[i][k]=f[f[i][k-1]][k-1];//i跳2^k步相当于i先跳2^(k-1)再跳2^(k-1)
            }
        }
    }
}
int lca(int a,int b)
{
    if(depth[b]>depth[a])swap(a,b);//让a在下面，深度大
    for(int k=15;k>=0;k--)//让a，b跳到同一层
        {
        if(depth[f[a][k]]>=depth[b])//哨兵的作用：如果跳出去了，depth[0]=0一定会小于右边,则不会跳
            {
            a=f[a][k];
            }
        }
    if(a==b)return a;//如果跳到同一个点。
    for(int k=15;k>=0;k--)//在同一层一起往上跳，直到跳到祖先的下面
        {
        if(f[a][k]!=f[b][k])//每次跳同样的步数，不会出现跳过lca的情况
            {
            a=f[a][k];
            b=f[b][k];
            }
        }
    return f[a][0];
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int u,v;
        cin>>u>>v;
        if(v==-1)root=u;
        else
        {
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    bfs(root);
    int q;
    cin>>q;
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        int p=lca(a,b);
        if (p == a) puts("1");
        else if (p == b) puts("2");
        else puts("0");
    }
    return 0;
}
