/*
分块大小 n/sqrt(m)n/sqrt(m)，复杂度 n∗sqrt(m)n∗sqrt(m)
可以处理n=1e5,m=1e6n=1e5,m=1e6的问题
玄学优化：奇数块右端点小到大，偶数块右端点大到小排序
 */

using namespace std;

const int N = 50010, M = 200010, S = 1000010;

int n, m, len;
int w[N], ans[M];
struct Query
        {
    int id, l, r;
        }q[M];
int cnt[S];

int get(int x)
{
    return x / len;
}

bool cmp(const Query& a, const Query& b)
{
    int i = get(a.l), j = get(b.l);
    if (i != j) return i < j;
    return a.r < b.r;
}

void add(int x, int& res)
{
    if (!cnt[x]) res ++ ;
    cnt[x] ++ ;
}

void del(int x, int& res)
{
    cnt[x] -- ;
    if (!cnt[x]) res -- ;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    scanf("%d", &m);
    len = max(1, (int)sqrt((double)n * n / m));

    for (int i = 0; i < m; i ++ )
    {
        int l, r;
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    sort(q, q + m, cmp);

    for (int k = 0, i = 0, j = 1, res = 0; k < m; k ++ )
    {
        int id = q[k].id, l = q[k].l, r = q[k].r;
        while (i < r) add(w[ ++ i], res);
        while (i > r) del(w[i -- ], res);
        while (j < l) del(w[j ++ ], res);
        while (j > l) add(w[ -- j], res);
        ans[id] = res;
    }

    for (int i = 0; i < m; i ++ ) printf("%d\n", ans[i]);
    return 0;
}
