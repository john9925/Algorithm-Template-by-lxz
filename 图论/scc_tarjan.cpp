#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int dfn[N],low[N],scc_cnt,id[N],Size[N],times,stk[N],top,dout[N];
bool in[N];
vector<int>g[N];
void tarjan(int u)
{
    dfn[u]=low[u]=++times;
    stk[++top]=u,in[u]=1;
    for(auto j:g[u])
    {
        if(!dfn[j])
        {
            tarjan(j);
            low[u]=min(low[u],low[j]);
        }
        else if(in[j])
            low[u]=min(low[u],dfn[j]);
    }
    if(dfn[u]==low[u])
    {
        int y;
        scc_cnt++;
        do
        {
            y=stk[top--];
            in[y]=0;
            id[y]=scc_cnt;
            Size[scc_cnt]++;
        }while(y!=u);
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
    for(int i=1;i<=n;i++)
        for(auto j:g[i])
        {
            int a=id[i],b=id[j];
            if(a!=b)dout[a]++;
        }
    int zeros=0,sum=0;
    for(int i=1;i<=scc_cnt;i++)
    {
        if(!dout[i])
        {
            zeros++;
            sum+=Size[i];
            if(zeros>1)
            {
                sum=0;
                break;
            }
        }
    }
    cout<<sum;
}
