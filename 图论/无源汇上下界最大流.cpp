/*
无源汇上下界可行流
每条边的容量有上界和下界要求，求最大流。
让上界-下界为容量。流量-下界为新图流量。这样操作以后满足容量限制，但流量守恒不满足。
看入边减的多的话就从S连一条边过去。否则连到T
最终从S连出去的流必须都是满的，因为原图中流量是守恒的。每条边的流量-下界以后。就不守恒了。

f[i^1]则是新图中边i的流量。加上l[i]就是实际的流量
*/
#include<bits/stdc++.h>
using namespace std;
const int N=205,M=50200,inf=0x3f3f3f3f;
int h[N],ne[M],e[M],idx,f[M],l[M];
int q[N],cur[N],d[N],A[N],S,T;
void add(int a,int b,int c,int d)
{
    e[idx]=b,f[idx]=d-c,l[idx]=c,ne[idx]=h[a],h[a]=idx++;
    e[idx]=a,f[idx]=0,ne[idx]=h[b],h[b]=idx++;
}
bool bfs()
{
    int hh=0,tt=0;
    memset(d,-1,sizeof d);
    q[0]=S,cur[S]=h[S],d[S]=0;
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
                if(j==T)return 1;
                q[++tt]=j;
            }
        }
    }
    return 0;
}
int find(int u,int limit)
{
    if(u==T)return limit;
    int flow=0;
    for(int i=cur[u];~i&&flow<limit;i=ne[i])
    {
        int j=e[i];
        cur[u]=i;
        if(d[j]==d[u]+1&&f[i])
        {
            int t=find(j,min(f[i],limit-flow));
            if(!t)d[j]=-1;
            flow+=t;
            f[i]-=t,f[i^1]+=t;
        }
    }
    return flow;
}
int dinic()
{
    int res=0;
    while(bfs())res+=find(S,inf);
    return res;
}
int main()
{
    memset(h,-1,sizeof h);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        add(a,b,c,d);
        A[a]-=c,A[b]+=c;
    }
    S=0,T=n+1;
    int tot=0;
    for(int i=1;i<=n;i++)
    {
        if(A[i]>0)add(S,i,0,A[i]),tot+=A[i];
        else add(i,T,0,-A[i]);
    }
    if(dinic()!=tot)puts("NO");
    else
    {
        puts("YES");
        for(int i=0;i<m*2;i+=2)printf("%d\n",f[i^1]+l[i]);
    }
    return 0;
}