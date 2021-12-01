//给定 n 个整数（可能重复），现在需要从中挑选任意个整数，使得选出整数的异或和最大。
//请问，这个异或和的最大可能值是多少。
//从高位到低位枚举，如果异或上线性基的数结果变大就异或他，否则不异或他
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll d[N];
void add(ll x)
{
    for(int i=62;i>=0;i--)
    {
        if(x&(1ll<<i))//注意，如果i大于31，前面的1的后面一定要加ll
            {
            if(d[i])x^=d[i];
            else
            {
                d[i]=x;
                break;//插入成功就退出
            }
            }
    }
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        ll x;
        scanf("%lld",&x);
        add(x);
    }
    ll ans=0;
    for(int i=62;i>=0;i--)ans=max(ans,ans^d[i]);//注意从大到小
    cout<<ans;
    return 0;
}