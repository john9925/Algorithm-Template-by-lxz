//普通bsgs
//复杂度O（根号p）。求a^x=b(%p)的最小非负整数解x。要求a和p互质。扩展的bsgs则不要求互质，可以直接用扩展的
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

typedef long long LL;

int bsgs(int a, int b, int p)
{
    if (1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    unordered_map<int, int> hash;
    for (int i = 0, j = b % p; i < k; i ++ )
    {
        hash[j] = i;
        j = (LL)j * a % p;
    }
    int ak = 1;
    for (int i = 0; i < k; i ++ ) ak = (LL)ak * a % p;

    for (int i = 1, j = ak; i <= k; i ++ )
    {
        if (hash.count(j)) return (LL)i * k - hash[j];
        j = (LL)j * ak % p;
    }
    return -1;
}

int main()
{
    int a, p, b;
    while (cin >> a >> p >> b, a || p || b)
    {
        int res = bsgs(a, b, p);
        if (res == -1) puts("No Solution");
        else cout << res << endl;
    }
    return 0;
}

//扩展bsgs
//给定整数 a,p,b。
//求满足 a^x≡b(modp) 的最小非负整数 x。
//1≤a,p≤2^31−1,
//0≤b≤2^31−1
//如果有 x 满足该要求，输出最小的非负整数 x，否则输出 No Solution。
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

typedef long long LL;
const int INF = 1e8;

int exgcd(int a, int b, int& x, int& y)
{
    if (!b)
    {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int bsgs(int a, int b, int p)
{
    if (1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    unordered_map<int, int> hash;
    for (int i = 0, j = b % p; i < k; i ++ )
    {
        hash[j] = i;
        j = (LL)j * a % p;
    }
    int ak = 1;
    for (int i = 0; i < k; i ++ ) ak = (LL)ak * a % p;
    for (int i = 1, j = ak; i <= k; i ++ )
    {
        if (hash.count(j)) return i * k - hash[j];
        j = (LL)j * ak % p;
    }
    return -INF;
}

int exbsgs(int a, int b, int p)
{
    b = (b % p + p) % p;
    if (1 % p == b % p) return 0;
    int x, y;
    int d = exgcd(a, p, x, y);
    if (d > 1)
    {
        if (b % d) return -INF;
        exgcd(a / d, p / d, x, y);
        return exbsgs(a, (LL)b / d * x % (p / d), p / d) + 1;
    }
    return bsgs(a, b, p);
}

int main()
{
    int a, p, b;
    while (cin >> a >> p >> b, a || p || b)
    {
        int res = exbsgs(a, b, p);
        if (res < 0) puts("No Solution");
        else cout << res << endl;
    }
    return 0;
}
