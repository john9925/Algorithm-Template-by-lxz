//On求阶乘的质因数分解
//首先把n以内质数全部打出来，然后枚举每个质数，计算次幂。
//比如p^n，在p^1被+1，在p^2被+1，最终会加n次。比如2345678 2^1 贡献4， 2^2贡献2 2^4贡献1
//复杂度n/ln(n)*ln(n)=On
//        枚举倍数的时候记得开ll

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000010;

int primes[N], cnt;
bool st[N];

void init(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] * i <= n; j ++ )
        {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    init(n);

    for (int i = 0; i < cnt; i ++ )//枚举每个质因数
        {
        int p = primes[i];
        int s = 0;
        //for (int j = n; j; j /= p) s += j / p;
        for(long long i=p;i<=n;i*=p)s+=n/i;//计算p的倍数个数+p^2个数倍数+.....
        printf("%d %d\n", p, s);
        }

    return 0;
}