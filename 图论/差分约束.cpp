
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=3e5+10;
typedef long long ll;
bool st[N];
int n,k,stk[N],cnt[N],dis[N];
int h[N], e[M], w[M], ne[M], idx;
void add(int a,int b,int c)
{
    e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}
bool spfa()
{
    int tt=0,hh=0;
    stk[++tt]=0;
    st[0]=1;
    cnt[0]++;
    while(hh!=tt)
    {
        int t=stk[tt--];
        st[t]=0;
        for(int i=h[t];~i;i=ne[i])
        {
            int to=e[i],cost=w[i];
            if(dis[to]<dis[t]+cost)
            {
                dis[to]=dis[t]+cost;
                if(!st[to])
                {
                    st[to]=1;
                    cnt[to]++;
                    if(cnt[to]>n)return 0;//有正环
                    stk[++tt]=to;
                }
            }
        }
    }
    return 1;
}
int main()
{
    memset(h,-1,sizeof h);
    cin>>n>>k;
    for(int i=1;i<=k;i++)
    {
        int x,a,b;
        scanf("%d %d %d",&x,&a,&b);
        if (x == 1) add(b, a, 0), add(a, b, 0);
        else if (x == 2) add(a, b, 1);
        else if (x == 3) add(b, a, 0);
        else if (x == 4) add(b, a, 1);
        else add(a, b, 0);
    }
    for(int i=1;i<=n;i++)add(0, i, 1);//xi>=1 <=> xi>=x0+1

    ll res=0;
    if(spfa())
    {
        for(int i=1;i<=n;i++)res+=dis[i];
        printf("%lld",res);
    }
    else puts("-1");
    return 0;
}