#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int d[N],st[N],cnt[N],n,m;//st表示x在不在队列中
#define pii pair<int,int>
vector<pii>g[N];
int spfa(int x)
{
    memset(d,0x3f,sizeof(d));
    queue<int>q;
    for(int i=1;i<=n;i++)
    {
        q.push(i);
        st[i]=1;
        cnt[i]++;
    }
    while(q.size())
    {
        auto t=q.front();
        q.pop();
        st[t]=0;//每个点可能进队多次
        for(auto i:g[t])
        {
            int a=i.first,b=i.second;
            if(d[a]>d[t]+b)//每次a更新，肯定是因为t更新了，下次c更新则是因为a
                {
                d[a]=d[t]+b;
                if(!st[a])
                {
                    q.push(a);
                    st[a]=1;
                    cnt[a]++;//若某个点进队大于等于n次，则有负环。写大于好像也可以
                    if(cnt[a]>=n)
                    {
                        return 1;
                    }
                }
                }
        }
    }
    return 0;

}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g[u].push_back({v,w});
    }
    int t=spfa(1);
    if(t==1)puts("Yes");
    else puts("No");
    return 0;
}