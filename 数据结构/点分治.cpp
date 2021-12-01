/*
点分治
1.连通块内的答案
2.重心连接两个连通块的点的答案（get所有连通块的点-sum：get（某个连通块的点））就是答案。容斥的思想，因为一个联通块内肯定是自己块内选两个点，而不是自己跑到重心又跑回来自己联通块。
3.路径有一端是重心
 */
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
#define pii pair<int,int>
int n,m;
int p[N],q[N];//p存的是所有连通块中的点到重心的距离，q存的是某连通块中的点到重心的距离
vector<pii>g[N];
bool st[N];
int get_wc(int u,int fa,int tot,int &wc)//求重心（不一定是重心，但满足时间复杂度要求），返回值sz是包含u的子树大小
{
    if(st[u])return 0;
    int ms=0,sz=1;
    for(auto i:g[u])
    {
        if(i.first==fa)continue;
        int t=get_wc(i.first,u,tot,wc);
        sz+=t;
        ms=max(ms,t);
    }
    ms=max(ms,tot-sz);//ms是最大的连通块大小，tot-sz表示父连通块大小。
    if(ms<=tot/2)wc=u;//满足时间复杂度的要求，每个连通块必须是原大小/2，
    return sz;
}
int get_size(int u,int fa)//u为子树的大小
{
    if(st[u])return 0;
    int res=1;
    for(auto i:g[u])
    {
        if(i.first==fa)continue;
        res+=get_size(i.first,u);
    }
    return res;
}
void get_dis(int u,int fa,int dis,int &qt)//求u子树到重心的距离
{
    if(st[u])return ;
    q[qt++]=dis;
    for(auto i:g[u])
    {
        if(i.first==fa)continue;
        get_dis(i.first,u,dis+i.second,qt);
    }
}
int get(int a[],int k)//求a中任取两点和<=m的方案数
{
    sort(a,a+k);
    int ans=0;
    for(int i=0;i<k;i++)
    {
        int r=upper_bound(a,a+k,m-a[i])-a;
        r--;
        if(r<=i)break;
        ans+=r-i;
    }
    return ans;
}
int cal(int u)
{
    if(st[u])return 0;
    get_wc(u,-1,get_size(u,-1),u);//求重心
    st[u]=1;
    int pt=0,res=0;//pt是p数组大小
    for(auto i:g[u])//遍历被重心划分的每一个连通块
        {
        int qt=0;
        get_dis(i.first,u,i.second,qt);//计算被重心划分的每个连通块中的点到重心的距离，存在q中
        for(int j=0;j<qt;j++)
        {
            if(q[j]<=m)res++;//同一连通块中任意点到重心距离<=m也是合法方案
            p[pt++]=q[j];
        }
        res-=get(q,qt);//减掉同一连通块中任意两点到重心距离和<=m的方案数。
        }
    res+=get(p,pt);//pt存所有的点
    for(auto i:g[u])res+=cal(i.first);//递归的答案
    return res;
}
int main()
{
    while(cin>>n>>m)
    {
        if(n==0&&m==0)break;
        for(int i=0;i<=n;i++)g[i].clear(),st[i]=0;
        for(int i=1;i<=n-1;i++)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            g[a].push_back({b,c});
            g[b].push_back({a,c});
        }
        printf("%d\n",cal(0));
    }
    return 0;
}