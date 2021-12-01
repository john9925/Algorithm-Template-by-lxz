//完全背包，每件物品可以无限用
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int f[maxn],v[maxn],w[maxn];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
    {
        for(int j=v[i];j<=m;j++)//从小到大，保证是f[i][]..(用的是这层的来更新)
            {
            if(j>=v[i])f[j]=max(f[j],f[j-v[i]]+w[i]);
            }
    }
    cout<<f[m];
    return 0;
}