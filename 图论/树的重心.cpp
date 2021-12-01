/*
1。树中所有点到某个点的距离和中，到重心的距离和是最小的，如果有两个重心，他们的距离和一样。
2。把两棵树通过一条边相连，新的树的重心在原来两棵树重心的连线上。
3。一棵树添加或者删除一个节点，树的重心最多只移动一条边的位置。
4。一棵树最多有两个重心，且相邻。
 */
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
vector<int>g[N];
#define pb push_back
int n,ans=N,st[N];
int dfs(int u)//返回以u为根结点的树的点个数，包括u
{
    int sum=1;//以u为根结点的树的点个数，包括u
    int res=0;//以当前点为重心（删掉该点），（剩余）最大的联通块点的个数
    st[u]=1;
    for(auto i:g[u])
    {
        if(!st[i])
        {
            int s=dfs(i);
            sum+=s;
            res=max(res,s);
        }
    }
    res=max(res,n-sum);
    ans=min(ans,res);// 所有最大中选最小的出来

    return sum;
}
int main()
{
    cin>>n;
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1);
    cout<<ans;
}
/*
 * https://vjudge.net/contest/468038#problem/M
 * 询问每个子树的重心，核心思路是重心一直往上走，On。
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,sz[N],f[N],son[N],d[N];
vector<int>g[N];
void find(int rt,int x,int y)
{
    while(d[x]>d[rt]&&sz[x]<sz[rt]-sz[x])x=f[x];
    while(d[y]>d[rt]&&sz[y]<sz[rt]-sz[y])y=f[y];
    if(d[y]>d[x])son[rt]=y;
    else son[rt]=x;
}
void dfs(int u,int fa)
{
    f[u]=fa;
    sz[u]=1;
    son[u]=u;
    for(auto i:g[u])
    {
        if(i==fa)continue;
        d[i]=d[u]+1;
        dfs(i,u);
        sz[u]+=sz[i];
        f[i]=u;
        find(u,son[u],son[i]);
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        u=read(),v=read();
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++)
    {
        bool flag=0;
        if(son[i]!=1&&sz[son[i]]==sz[i]-sz[son[i]])flag=1;
        if(flag)printf("%d %d\n",min(son[i],f[son[i]]),max(son[i],f[son[i]]));
        else printf("%d\n",son[i]);
    }
    return 0;
}
