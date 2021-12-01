/*
最大流
dinic 求最大流 O(n2mn2m) 多路增广 可以处理10000-100000的网络
三个重要优化
1.当前弧优化cur，直接从还没流满的边开始
2.flow<limit 当前u点后面的总流量小于limit
3.废点优化 该点dfs找不到可行的流，把那个点的层设为-1

bfs() ：返回有无增广路，有的话会顺便建立分层图（避免后面搜的时候遇到环）
注意表头初始化-1
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10,M=2e5+10,inf=0x3f3f3f3f;
int h[N],e[M],ne[M],f[M],idx;
int d[N],q[N],cur[N];//d表示点i的层数，cur表示点i直接从cur[i]这条边开始
int n,m,S,T;
void add(int a,int b,int c)
{
    e[idx]=b,f[idx]=c,ne[idx]=h[a],h[a]=idx++;
    e[idx]=a,f[idx]=0,ne[idx]=h[b],h[b]=idx++;
}
bool bfs()//返回有无增广路，有的话会顺便建立分层图（避免后面搜的时候遇到环）
{
    int hh=0,tt=0;
    memset(d,-1,sizeof d);
    q[0]=S;
    d[S]=0;
    cur[S]=h[S];
    while(hh<=tt)
    {
        int t=q[hh++];
        for(int i=h[t];~i;i=ne[i])
        {
            int j=e[i];
            if(d[j]==-1&&f[i])
            {
                d[j]=d[t]+1;
                cur[j]=h[j];
                if(j==T)return 1;//遇到层数比T大的点，如果他有可行流到T，总会在某次bfs被搜出来
                q[++tt]=j;
            }
        }
    }
    return 0;
}
int find(int u,int limit)//limit表示u前面的最大流量(最小容量)
{
    if(u==T)return limit;
    int flow=0;//flow表示从u开始的总流量
    //直接从当前弧开始，且u后面的总流量必须小于前面的流量限制limit，流入流出守恒。
    for(int i=cur[u];~i&&flow<limit;i=ne[i])
    {
        cur[u]=i;//到i这条边，说明前面的边都满了。
        int j=e[i];
        if(d[j]==d[u]+1&&f[i])//必须是下一层，且有容量
            {
            //u后面已经流了flow，u前面流入limit。所以u后面还能流limit-flow
            int t=find(j,min(limit-flow,f[i]));//返回j点开始最大流量
            if(!t)d[j]=-1;
            f[i]-=t,f[i^1]+=t,flow+=t;
            }
    }
    return flow;
}
int dinic()
{
    int r=0;
    while(bfs())r+=find(S,inf);//从S开始流量限制为inf
    return r;
}
int main()
{
    memset(h,-1,sizeof h);
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(int i=1;i<=m;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    printf("%d",dicnic());
    return 0;
}
