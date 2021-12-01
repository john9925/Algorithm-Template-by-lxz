/*
边双连通分量
给一个无向连通图，求加几条边变成一个边双连通分量。
无向图缩点后为一棵树，只剩下桥和点
答案为树的(叶子节点数+1)/2下取整
 */
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5010, M = 20010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];
int d[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u, int from)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j, i);
            //sz[u]+=sz[j]+1; sz[j]是j这个子树的边数
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j])
                is_bridge[i] = is_bridge[i ^ 1] = true;//加边的时候01，23，45是一对边
        }
        else if (i != (from ^ 1))
        {
            low[u] = min(low[u], dfn[j]);
            //sz[j]++;
        }
    }

    if (dfn[u] == low[u])
    {
        ++ dcc_cnt;
        int y;
        do {
            y = stk[top -- ];
            id[y] = dcc_cnt;
        } while (y != u);
    }
}

int main()
{
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    tarjan(1, -1);
    for (int i = 0; i < idx; i ++ )
        if (is_bridge[i])
            d[id[e[i]]] ++ ;

        int cnt = 0;
        for (int i = 1; i <= dcc_cnt; i ++ )
            if (d[i] == 1)
                cnt ++ ;

            printf("%d\n", (cnt + 1) / 2);

            return 0;
}
