//FFT
//
//nlogn 求两个多项式乘（卷积）
//数组开4倍
//使用分治时，将其他无关的位置置为0，记得循环到limit
//p 一般取998244353,1004535809,469762049
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 300010;
const double PI = acos(-1);

int n, m;
struct Complex
        {
    double x, y;
    Complex operator+ (const Complex& t) const
    {
        return {x + t.x, y + t.y};
    }
    Complex operator- (const Complex& t) const
    {
        return {x - t.x, y - t.y};
    }
    Complex operator* (const Complex& t) const
    {
        return {x * t.x - y * t.y, x * t.y + y * t.x};
    }
        }a[N], b[N];
int rev[N], bit, tot;

void fft(Complex a[], int inv)
{
    for (int i = 0; i < tot; i ++ )
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
        for (int mid = 1; mid < tot; mid <<= 1)
        {
            auto w1 = Complex({cos(PI / mid), inv * sin(PI / mid)});
            for (int i = 0; i < tot; i += mid * 2)
            {
                auto wk = Complex({1, 0});
                for (int j = 0; j < mid; j ++, wk = wk * w1)
                {
                    auto x = a[i + j], y = wk * a[i + j + mid];
                    a[i + j] = x + y, a[i + j + mid] = x - y;
                }
            }
        }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i ++ ) scanf("%lf", &a[i].x);
    for (int i = 0; i <= m; i ++ ) scanf("%lf", &b[i].x);
    while ((1 << bit) < n + m + 1) bit ++;
    tot = 1 << bit;
    for (int i = 0; i < tot; i ++ )
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    fft(a, 1), fft(b, 1);
    for (int i = 0; i < tot; i ++ ) a[i] = a[i] * b[i];
    fft(a, -1);
    for (int i = 0; i <= n + m; i ++ )
        printf("%d ", (int)(a[i].x / tot + 0.5));//+0.5因为是浮点，怕误差。

        return 0;
}
//NTT
#include<bits/stdc++.h>
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF : *p1++)
#define swap(x, y) x ^= y, y ^= x, x ^= y
#define LL long long
const int MAXN = 3 * 1e6 + 10, P = 998244353, G = 3, Gi = 332748118;
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int N, M, limit = 1, L, r[MAXN];
LL a[MAXN], b[MAXN];

inline LL fastpow(LL a, LL k)
{
    LL base = 1;
    while (k)
    {
        if (k & 1) base = (base * a) % P;
        a = (a * a) % P;
        k >>= 1;
    }
    return base % P;
}

inline void NTT(LL *A, int type)
{
    for (int i = 0; i < limit; i++)
        if (i < r[i]) swap(A[i], A[r[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            LL Wn = fastpow(type == 1 ? G : Gi, (P - 1) / (mid << 1));
            for (int j = 0; j < limit; j += (mid << 1))
            {
                LL w = 1;
                for (int k = 0; k < mid; k++, w = (w * Wn) % P)
                {
                    int x = A[j + k], y = w * A[j + k + mid] % P;
                    A[j + k] = (x + y) % P,
                    A[j + k + mid] = (x - y + P) % P;
                }
            }
        }
}

int main()
{
    N = read();
    M = read();
    for (int i = 0; i <= N; i++) a[i] = (read() + P) % P;
    for (int i = 0; i <= M; i++) b[i] = (read() + P) % P;
    while (limit <= N + M) limit <<= 1, L++;
    for (int i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));
    NTT(a, 1);
    NTT(b, 1);
    for (int i = 0; i < limit; i++) a[i] = (a[i] * b[i]) % P;
    NTT(a, -1);
    LL inv = fastpow(limit, P - 2);
    for (int i = 0; i <= N + M; i++)
        printf("%d ", (a[i] * inv) % P);
    return 0;
}

//分治fft，n个多项式相乘，每个多项式都是1+aix这种
#include<bits/stdc++.h>
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1<<21, stdin), p1 == p2) ? EOF : *p1++)
#define swap(x, y) x ^= y, y ^= x, x ^= y
#define ll long long
const int MAXN = 3 * 1e6 + 10, P = 998244353, G = 3, Gi = 332748118;
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int N, M, limit = 1, L, r[MAXN];
ll a[MAXN], b[MAXN];

inline ll fastpow(ll a, ll k)
{
    ll base = 1;
    while (k)
    {
        if (k & 1) base = (base * a) % P;
        a = (a * a) % P;
        k >>= 1;
    }
    return base % P;
}

void ini(int len)
{
    limit = 1, L = 0;
    while (limit <= len) limit <<= 1, L++;
    for (int i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));
}

inline void NTT(ll *A, int type)
{
    for (int i = 0; i < limit; i++)
        if (i < r[i]) swap(A[i], A[r[i]]);
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            ll Wn = fastpow(type == 1 ? G : Gi, (P - 1) / (mid << 1));
            for (int j = 0; j < limit; j += (mid << 1))
            {
                ll w = 1;
                for (int k = 0; k < mid; k++, w = (w * Wn) % P)
                {
                    int x = A[j + k], y = w * A[j + k + mid] % P;
                    A[j + k] = (x + y) % P,
                    A[j + k + mid] = (x - y + P) % P;
                }
            }
        }
}

ll w[MAXN],g[MAXN];

void solve(int l, int r, vector<ll> &f)
{
    if (l == r)
    {
        f[0]=1;
        f[1]=a[l];
        return;
    }
    int mid = l + r >> 1;
    int len1=mid-l+1,len2=r-mid;
    vector<ll>f1(len1+5),f2(len2+5);
    solve(l,mid,f1);
    solve(mid+1,r,f2);
    for(int i=0;i<=len1;i++)w[i]=f1[i];
    for(int i=0;i<=len2;i++)g[i]=f2[i];
    int len=len1+len2;
    ini(len);
    for(int i=len1+1;i<limit;i++)w[i]=0;
    for(int i=len2+1;i<limit;i++)g[i]=0;
    NTT(w, 1);
    NTT(g, 1);
    for (int i = 0; i < limit; i++) w[i] = (w[i] * g[i]) % P;
    NTT(w, -1);
    ll inv = fastpow(limit, P - 2);
    for (int i=0;i<=len;i++)f[i] = w[i] * inv % P;
}
ll in[MAXN];
int main()
{
    int t;
    t = read();
    in[0]=1;
    for(ll i=1;i<MAXN;i++)in[i]=in[i-1]*i%P;
    while(t--)
    {
        N = read();
        for (int i = 1; i <= N ; i++) a[i] = (read() + P) % P;
        vector<ll>ans(N+5);
        solve(1,N,ans);
        ll res=0;
        for(int i=1;i<=N;i++)
        {
            //cout<<ans[i]<<endl;
            res=(res+ans[i]*in[i]%P*in[N-i]%P)%P;
        }
        printf("%lld\n",res*fastpow(in[N],P-2)%P);
    }
    return 0;
}
