/*
给定一张无向图，求图中一个至少包含 3 个点的环，环上的节点不重复，并且环上的边的长度之和最小。
该问题称为无向图的最小环问题。
你需要输出最小环的方案，若最小环不唯一，输出任意一个均可。

 floyd找最小环。可以将环分类为环上最大的点的编号为k。floyd其实是插点法。当最外层循环到k时，
 i,j之间的最短路由(1~k-1)这些点更新，这时候就可以顺便枚举环上最大点为k了。在最内层循环记得记录pos[i][j]表示，
 i与j之间的最短路由k点转移来。
 */
#include<bits/stdc++.h>
using namespace std;
const int N=105,inf=0x3f3f3f3f;
int g[N][N],dis[N][N],path[N],n,m,cnt,pos[N][N];
void getpath(int i,int j)//递归输出i，j之间的路径，不包括ij
{
    if(pos[i][j]==0)return ;//ij之间没被其他点更新
    int k=pos[i][j];
    getpath(i,k);//左边
    path[cnt++]=k;
    getpath(k,j);//右边
}
int main()
{
    cin>>n>>m;
    memset(g,0x3f,sizeof g);
    for(int i=1;i<=n;i++)g[i][i]=0;
    for(int i=1;i<=m;i++)
    {
        int a,b,w;
        cin>>a>>b>>w;
        g[a][b]=g[b][a]=min(g[b][a],w);//可能有重边
    }
    int res=inf;
    memcpy(dis,g,sizeof g);
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<k;i++)//枚举ij的点对就可以了。
            for(int j=i+1;j<k;j++)
            {
                if((long long)dis[i][j]+g[i][k]+g[k][j]<res)
                {
                    res=dis[i][j]+g[i][k]+g[k][j];
                    cnt=0;
                    path[cnt++]=k;
                    path[cnt++]=i;
                    getpath(i,j);
                    path[cnt++]=j;
                }
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(dis[i][j]>dis[i][k]+dis[k][j])
                {
                    dis[i][j]=dis[i][k]+dis[k][j];
                    pos[i][j]=k;
                }
            }
    }
    if(res!=inf)
    {
        for(int i=0;i<cnt;i++)printf("%d ",path[i]);
    }
    else puts("No solution.");
    return 0;
}
