/*
有 N 组物品和一个容量是 V 的背包。
每组物品有若干个，同一组内的物品最多只能选一个。
每件物品的体积是 vij，价值是 wij，其中 i 是组号，j 是组内编号。
求解将哪些物品装入背包，可使物品总体积不超过背包容量，且总价值最大。
输出最大价值。
 */
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int f[N],v[N],w[N];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        int s;
        cin>>s;
        for(int j=0;j<s;j++)cin>>v[j]>>w[j];
        for(int j=m;j>=0;j--)
        {
            for(int k=0;k<s;k++)
            {
                if(j>=v[k])f[j]=max(f[j],f[j-v[k]]+w[k]);
            }
        }
    }
    cout<<f[m];
    return 0;
}