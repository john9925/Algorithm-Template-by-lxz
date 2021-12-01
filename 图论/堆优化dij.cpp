#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int d[N],n,m;;
#define pii pair<int,int>
vector<pii>g[N];
int dijkstra(int x)
{
    memset(d,0x3f,sizeof(d));
    priority_queue<pii,vector<pii>,greater<pii>>p;
    p.push({0,1});
    d[1]=0;//别漏了初始化
    while(p.size())
    {
        auto t=p.top();
        p.pop();
        int dis=t.first,ver=t.second;

        if(d[ver]<dis) continue;
        for(auto i:g[ver])
        {
            int to=i.first,val=i.second;
            if(d[to]>d[ver]+val)
            {
                d[to]=d[ver]+val;
                p.push({d[to],to});
            }
        }
    }
    if(d[n]==0x3f3f3f3f)return -1;
    else return d[n];

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
    cout<<dijkstra(1);
    return 0;
}
