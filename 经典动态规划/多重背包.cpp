//多重背包，第i件物品有si件。
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+10;
int f[maxn];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int v,w,s;
        cin>>v>>w>>s;
        for(int j=m;j>=0;j--)
        {
            //f[i][j]=f[i-1][j];
            for(int k=0;k<=s&&k*v<=j;k++)
            {
                f[j]=max(f[j],f[j-k*v]+k*w);
            }

        }
    }
    cout<<f[m];
    return 0;
}
/*
多重背包问题II。每个物品之只有s件。时间复杂度要求更高。2*10^7.
将背包用二进制拆开，变成01背包问题。如10，拆成1 2 4 3 ，用这4个数可以表示0-10的数
 */
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int f[N];
int main()
{
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>>goods;//fi 体积 se价值
    for(int i=1;i<=n;i++)
    {
        int v,w,s;
        cin>>v>>w>>s;
        for(int k=1;k<=s;k*=2)//把s拆分成几个物品，变成01背包
            {
            s-=k;
            goods.push_back({k*v,k*w});
            }
        if(s>0)goods.push_back({s*v,s*w});
    }
    for(auto i:goods)
    {
        for(int j=m;j>=i.first;j--)f[j]=max(f[j],f[j-i.first]+i.second);
    }
    cout<<f[m];
}