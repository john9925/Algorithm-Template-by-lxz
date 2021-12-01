#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2000010;

int n, p;
int primes[N], cnt;
bool st[N];

void init(int n)
{
    for(int i=2;i<=n;i++)
    {
        if(!st[i]) primes[cnt++]=i;
        for(int j=0;primes[j]*i<=n;j++)
        {
            st[primes[j]*i]=true;
            if(i%primes[j]==0)break;
        }
    }
}

int qmi(int a,int k)
{
    int res = 1;
    while(k)
    {
        if(k&1) res = (LL)res*a%p;
        a = (LL)a*a%p;
        k>>=1;
    }
    return res;
}

int get(int n,int p)
{
    int s = 0;
    while(n)
    {
        s+=n/p;
        n/=p;
    }
    return s;
}

int C(int a,int b)
{
    int res = 1;
    for(int i=0;i<cnt;i++)
    {
        int prime = primes[i];
        // C_{a}^{b} = a!/b!(a-b)!
        int s = get(a,prime)-get(b,prime)-get(a-b,prime);
        res = (LL)res*qmi(prime,s)%p;
    }
    return res;
}

int main()
{
    scanf("%d%d", &n, &p);
    init(n * 2);

    cout << (C(n * 2, n) - C(n * 2, n - 1) + p) % p << endl;

    return 0;
}