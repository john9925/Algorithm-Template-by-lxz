//注意n在调用了solve以后就可能会改变。1e10的时候复杂度接近3e7.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000000 + 10;
int prime[N], id1[N], id2[N], flag[N], ncnt, m;
ll g[N], sum[N], a[N], T;
ll n;

int ID(ll x) {
    return x <= T ? id1[x] : id2[n / x];
}

ll calc(ll x) {
    return x * (x + 1) / 2 - 1;
}

ll init(ll x) {
    T = sqrt(x + 0.5);
    for (int i = 2; i <= T; i++) {
        if (!flag[i]) prime[++ncnt] = i, sum[ncnt] = sum[ncnt - 1] + i;
        for (int j = 1; j <= ncnt && i * prime[j] <= T; j++) {
            flag[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    for (ll l = 1; l <= x; l = x / (x / l) + 1) {
        a[++m] = x / l;
        if (a[m] <= T) id1[a[m]] = m; else id2[x / a[m]] = m;
        g[m] = calc(a[m]);
    }
    for (int i = 1; i <= ncnt; i++)
        for (int j = 1; j <= m && (ll) prime[i] * prime[i] <= a[j]; j++)
            g[j] = g[j] - (ll) prime[i] * (g[ID(a[j] / prime[i])] - sum[i - 1]);
}

ll solve(ll x) {
    if (x <= 1) return x;
    return n = x, init(n), g[ID(n)];
}

int main() {
    int t;
    cin>>t;
    while(t--)
    {
        memset(g, 0, sizeof(g));
        memset(a, 0, sizeof(a));
        memset(sum, 0, sizeof(sum));
        memset(prime, 0, sizeof(prime));
        memset(id1, 0, sizeof(id1));
        memset(id2, 0, sizeof(id2));
        memset(flag, 0, sizeof(flag));
        ncnt = m = 0;
        scanf("%lld", &n);
        cout<<solve(n)<<endl;
    }
}

