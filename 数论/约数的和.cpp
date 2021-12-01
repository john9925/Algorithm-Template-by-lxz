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
    ll res=1;
    for(auto m:ms)
    {
        int p=m.first,a=m.second;
        ll t=1;
        while(a--)t=(t*p+1)%mod;//p+1,p^2+p+1
        res=res*t%mod;
    }
    cout<<res;
}