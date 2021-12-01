/*
2-Sat
每个条件包含两个命题的SAT问题，且命题取值0或者1

如：对于x1,x2,x3 使得x1∨x3,¬x2∨x3成立
把关系转化为-》的关系。且两边都建边，即别忘了逆否命题。
1.x和¬x在同一联通分量，则无解。
2.枚举所有xi，缩点找强连通分量，当xi所在的强连通分量的拓扑排序在¬xi所在的强连通分量的拓扑排序之后时，取x为True
 （让拓扑排序靠后的成立）

 1.aVb   非a->b 非b->a
 2.a=1   aVa
 3.a=0   非aV非a
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 2000010, M = 2000010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts, stk[N], top;
int id[N], cnt;
bool ins[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ ts;
    stk[ ++ top] = u, ins[u] = true;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (ins[j]) low[u] = min(low[u], dfn[j]);
    }

    if (low[u] == dfn[u])
    {
        int y;
        cnt ++ ;
        do
        {
            y = stk[top -- ], ins[y] = false, id[y] = cnt;
        } while (y != u);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    while (m -- )
    {
        int i, a, j, b;
        scanf("%d%d%d%d", &i, &a, &j, &b);
        i --, j -- ;
        add(2 * i + !a, 2 * j + b);
        add(2 * j + !b, 2 * i + a);
    }

    for (int i = 0; i < n * 2; i ++ )
        if (!dfn[i])
            tarjan(i);
        for (int i = 0; i < n; i ++ )
            if (id[i * 2] == id[i * 2 + 1])
            {
                puts("IMPOSSIBLE");
                return 0;
            }

        puts("POSSIBLE");
            for (int i = 0; i < n; i ++ )
                if (id[i * 2] < id[i * 2 + 1]) printf("0 ");//让拓扑排序靠前的满足
                else printf("1 ");
                return 0;
}
