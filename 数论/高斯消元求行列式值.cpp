/*
 * 取模
算出来的都是非负的
 */
typedef long long ll;
ll A[110][110];

const int mod=1e9+7;

ll quick_pow(ll a, ll n, ll mod) {
    ll ans = 1;
    while(n) {
        if(n & 1) ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

ll inv(ll a) {
    return quick_pow(a, mod - 2, mod);
}

ll gauss(int n){
    ll ans = 1;
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++) {
            if(A[j][i]){
                for(int k = i; k <= n; k++) swap(A[i][k], A[j][k]);
                if(i != j) ans = -ans;
                break;
            }
        }
        if(!A[i][i]) return 0;
        for(ll j = i + 1, iv = inv(A[i][i]); j <= n; j++) {
            ll t = A[j][i] * iv % mod;
            for(int k = i; k <= n; k++)
                A[j][k] = (A[j][k] - t * A[i][k] % mod + mod) % mod;
        }
        ans = (ans * A[i][i] % mod + mod) % mod;
    }
    return ans;
}
//double
int Gauss1()
{
    for(int i=1;i<=n;i++){
        int p=i;
        while(!f[p][i] and p<=n)p++;
        if(p>=n+1)return 0;
        if(p!=i)swap(f[i],f[p]);
        for(int j=i+1;j<=n;j++)
        {
            double tmp=f[j][i]/f[i][i];
            for(int k=i;k<=n;k++)
                f[j][k]-=f[i][k]*tmp;
        }
    }
    double ans=1;
    for(int i=1;i<=n;i++)
        ans*=f[i][i];
    return (int)(ans+0.5);
}
