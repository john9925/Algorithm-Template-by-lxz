#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
typedef long long ll;
unordered_map<ll,ll>ms;
int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int x;
        cin>>x;
        for(int i=2;i<=x/i;i++)//对每一个数质因数分解，把底数相同的指数加起来
        {
            while(x%i==0)
            {
                x/=i;
                ms[i]++ ;
            }
        }
        if(x>1)ms[x]++;
    }
    ll ans=1;
    for(auto m:ms)
    {
        ans=ans*(m.second+1)%mod;
    }
    cout<<ans;
    return 0;
}
