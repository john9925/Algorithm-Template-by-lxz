//有 n 件物品和一个容量是 m 的背包，每件物品只能用一次，第 i 件物品的体积是 vi，价值是 wi。
//求解将哪些物品装入背包，可使这些物品的总体积不超过背包容量，且总价值最大。
//输出最大价值。
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int f[N];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int v,w;
        cin>>v>>w;
        for(int j=m;j>=v;j--)
        {
            f[j]=max(f[j],f[j-v]+w);
        }
    }
    cout<<f[m];
    return 0;
}
