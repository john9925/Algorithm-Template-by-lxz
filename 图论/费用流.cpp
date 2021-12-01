/*
费用流，最小费用最大流
 */
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 505, M = 100010, INF = 1e9;

int n, m, S, T;
ll h[N], e[M], f[M], w[M], ne[M], idx,num[N];
ll q[N], d[N], pre[N], incf[N];
bool st[N];

void add(int a, int b, int c, int d)
{
    e[idx] = b, f[idx] = c, w[idx] = d, ne[idx] = h[a], h[a] = idx ++ ;
    e[idx] = a, f[idx] = 0, w[idx] = -d, ne[idx] = h[b], h[b] = idx ++ ;
}

bool spfa()
{
    int hh = 0, tt = 1;
    memset(d, 0x3f, sizeof d);
    memset(incf, 0, sizeof incf);
    memset(pre,0,sizeof pre);
    memset(st,0,sizeof st);
    q[0] = S, d[S] = 0, incf[S] = INF;
    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i])
        {
            int ver = e[i];
            if (f[i] && d[ver] > d[t] + w[i])
            {
                d[ver] = d[t] + w[i];
                pre[ver] = i;
                incf[ver] = min(f[i], incf[t]);
                if (!st[ver])
                {
                    q[tt ++ ] = ver;
                    if (tt == N) tt = 0;
                    st[ver] = true;
                }
            }
        }
    }

    return incf[T] > 0;
}

void EK(ll& flow, ll& cost)
{
    flow = cost = 0;
    while (spfa())
    {
        ll t = incf[T];
        flow += t, cost += t * d[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1])
        {
            f[pre[i]] -= t;
            f[pre[i] ^ 1] += t;
        }
    }
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        idx=0;
        scanf("%d%d", &n, &m);
        memset(h, -1, sizeof h);
        ll sum=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d",&num[i]);
            sum+=num[i];
        }
        while (m -- )
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, INF, c);
            add(b, a, INF, c);
        }
        if(sum%n!=0)
        {
            puts("-1");
            continue;
        }
        S=0,T=n+1;
        sum/=n;
        ll totflow=0;
        for(int i=1; i<=n; i++)
        {
            if(num[i]>sum)add(S,i,num[i]-sum,0),totflow+=num[i]-sum;
            else if(num[i]<sum)add(i,T,sum-num[i],0);
        }
        ll flow, cost;
        EK(flow, cost);
        if(totflow==flow)printf("%lld\n",cost);//判断满流
        else puts("-1");
    }

    return 0;
}