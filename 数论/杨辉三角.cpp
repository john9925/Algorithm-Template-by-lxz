//2020/8/18
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
const int mod=1e9+7;
typedef long long ll;
ll c[N][N];
void ini()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<=i;j++)
        {
            if(!j)c[i][j]=1;//避免j==0时越界，同时i==0的越界的情况也处理了
            else c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
        }
    }
}
int main()
{
    int n;
    cin>>n;
    ini();
    while(n--)
    {
        int a,b;
        cin>>a>>b;
        printf("%d\n",c[a][b]);
    }
    return 0;
}
