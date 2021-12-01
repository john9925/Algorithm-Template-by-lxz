//求解n个。 x=ai%mi 其中mi不一定两两互质
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
int n;
ll exgcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){
        x = 1, y = 0;
        return a;
    }

    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
ll inline mod(ll a, ll b){
    return ((a % b) + b) % b;
}
int main(){
    while(~scanf("%lld",&n))
    {
        ll a1, m1;
        bool f=1;
        scanf("%lld%lld", &a1, &m1);
        for(int i = 1; i < n; i++){
            ll a2, m2, k1, k2;
            scanf("%lld%lld", &a2, &m2);
            ll d = exgcd(a1, -a2, k1, k2);
            if((m2 - m1) % d)
            {
                f=0;
            }
            k1 = mod(k1 * (m2 - m1) / d, abs(a2 / d));
            m1 = k1 * a1 + m1;
            a1 = abs(a1 / d * a2);
        }
        if(f)printf("%lld\n", m1);
        else puts("-1");
    }
    return 0;
}