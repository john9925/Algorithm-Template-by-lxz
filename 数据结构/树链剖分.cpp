/*
树链剖分，把树中某条路径转化为logn段区间。配合线段树等数据结构使用
因为dfs序先搜重儿子，所以重链节点编号是连续的。
*/
#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 100010, M = N * 2;

int n, m;
int w[N], h[N], e[M], ne[M], idx;
int id[N], nw[N], cnt;//dfs序，nw表示dfs序中，点的权值
int dep[N], sz[N], top[N], fa[N], son[N];//节点深度，子树大小，当前重链的顶点，当前点的父亲，当前点的重儿子
struct Tree
        {
    int l, r;
    LL add, sum;
        }tr[N * 4];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs1(int u, int father, int depth)//求重儿子
{
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == father) continue;
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;//重儿子子树节点更多
    }
}

void dfs2(int u, int t)//求dfs序，先遍历重儿子。t是顶点
{
    id[u] = ++ cnt, nw[cnt] = w[u], top[u] = t;
    if (!son[u]) return;//叶子结点
    dfs2(son[u], t);//先遍历重儿子
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j);//轻儿子的顶点就是自己
    }
}

void pushup(int u)
{
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u)
{
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add)
    {
        left.add += root.add, left.sum += root.add * (left.r - left.l + 1);
        right.add += root.add, right.sum += root.add * (right.r - right.l + 1);
        root.add = 0;
    }
}

void build(int u, int l, int r)
{
    tr[u] = {l, r, 0, nw[r]};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int k)
{
    if (l <= tr[u].l && r >= tr[u].r)
    {
        tr[u].add += k;
        tr[u].sum += k * (tr[u].r - tr[u].l + 1);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) update(u << 1, l, r, k);
    if (r > mid) update(u << 1 | 1, l, r, k);
    pushup(u);
}

LL query(int u, int l, int r)
{
    if (l <= tr[u].l && r >= tr[u].r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL res = 0;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

void update_path(int u, int v, int k)//将u到v的路径上的点加上k
{
    while (top[u] != top[v])//向上爬找到相同重链；同时维护所有经过的重链
        {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);//u比v更深
        update(1, id[top[u]], id[u], k);//重链顶点编号比当前点小。
        u = fa[top[u]];
        }
    if (dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k);
}

LL query_path(int u, int v)//求u到v路径的权值和
{
    LL res = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res += query(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    res += query(1, id[v], id[u]);
    return res;
}

void update_tree(int u, int k)//将子树都修改
{
    update(1, id[u], id[u] + sz[u] - 1, k);
}

LL query_tree(int u)//查询子树
{
    return query(1, id[u], id[u] + sz[u] - 1);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs1(1, -1, 1);
    dfs2(1, 1);
    build(1, 1, n);

    scanf("%d", &m);
    while (m -- )
    {
        int t, u, v, k;
        scanf("%d%d", &t, &u);
        if (t == 1)//u到v的路径上的点加上k
            {
            scanf("%d%d", &v, &k);
            update_path(u, v, k);
            }
        else if (t == 2)//u子树加上k
            {
            scanf("%d", &k);
            update_tree(u, k);
            }
        else if (t == 3)//查询u到v路径和
            {
            scanf("%d", &v);
            printf("%lld\n", query_path(u, v));
            }
        else printf("%lld\n", query_tree(u));//查询u的子树和
    }

    return 0;
}
