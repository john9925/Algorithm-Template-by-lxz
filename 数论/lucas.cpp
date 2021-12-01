//2020/8/28
/*
 lucas定理，用于求解组合数a，b非常大的时候，p小于等于1e5。把a，b处理到小于1e5然后用定义法nlogn解决
 */
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
int n,p;
ll a,b;
ll qp(ll a,ll b)
{
    ll res=1;
    while(b)
    {
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res%p;
}
ll C(ll a,ll b)
{
    ll res=1;
    for(int i=a,j=b;j>=1;j--,i--)
    {
        res=res*i%p;
        res=res*qp(j,p-2)%p;
    }
    return res;
}
ll lucas(ll a,ll b)
{
    if(a<p&&b<p)return C(a,b);
    else return C(a%p,b%p)*lucas(a/p,b/p)%p;
}
int main()
{
    cin>>n;
    while(n--)
    {
        cin>>a>>b>>p;
        cout<<lucas(a,b)<<endl;
    }
    return 0;
}
