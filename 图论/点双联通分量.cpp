//题意：删掉一个点后连通块数最多是多少
#include<bits/stdc++.h>
using namespace std;
const int N = 10010;
int n, m;
int dfn[N], low[N], timestamp;
int root, ans;
vector<int>g[N];
void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;

    int cnt = 0;
    for (auto j:g[u])
    {
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (low[j] >= dfn[u]) cnt ++ ;//说明u下面有一个子树，u可能是割点,具体看u是不是根讨论
        }
        else low[u] = min(low[u], dfn[j]);
    }

    if (u != root) cnt ++ ;//u不是根的话，说明该点上面还有一条边。(dfs搜索，如果这个点上面不止一条边，肯定被上面的某一条边搜掉了。)
    //if中的&&cnt可以去掉 如果cnt为0（不是割点） 那么删掉这个点还会有1个连通块
    ans = max(ans, cnt);
    /*判断割点
    if ((u != root&&cnt)||(u==root&&cnt>=2))
    {
        iscut[u]=1;
    }
    */
}

int main()
{
    while (scanf("%d%d", &n, &m), n || m)
    {
        memset(dfn, 0, sizeof dfn);
        timestamp = 0;
        for(int i=0;i<n;i++)g[i].clear();
        while (m -- )
        {
            int a, b;
            scanf("%d%d", &a, &b);
            g[a].push_back(b);
            g[b].push_back(a);
        }

        ans = 0;
        int cnt = 0;
        for (root = 0; root < n; root ++ )//以该点为根搜索
            if (!dfn[root])
            {
                cnt ++ ;
                tarjan(root);
            }

        printf("%d\n", ans + cnt - 1);
    }
    return 0;
}
/*
 * 题意：最少设置几个安全点，使任意删除一个点后，所有点均可以到达安全区。
tarjan 无向图点双连通分量缩点，割点最少会属于两个双连通分量。
 */
typedef unsigned long long ULL;

const int N = 1010;

int n, m;
int dfn[N], low[N], timestamp;
int stk[N], top;
int dcc_cnt;
vector<int> dcc[N],g[N];//dcc存这个块包含哪些点
bool cut[N];
int root;
void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u;

    if (u == root && !g[u].size())
    {
        dcc_cnt ++ ;
        dcc[dcc_cnt].push_back(u);
        return;
    }

    int cnt = 0;
    for (auto j:g[u])
    {
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j])
            {
                cnt ++ ;
                if (u != root || cnt > 1) cut[u] = true;
                ++ dcc_cnt;
                int y;
                do {
                    y = stk[top -- ];
                    dcc[dcc_cnt].push_back(y);
                } while (y != j);
                dcc[dcc_cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[j]);
    }
}

int main()
{
    int T = 1;
    while (cin >> m, m)
    {
        for (int i = 1; i <= dcc_cnt; i ++ ) dcc[i].clear();
        n = timestamp = top = dcc_cnt = 0;
        memset(dfn, 0, sizeof dfn);
        memset(cut, 0, sizeof cut);

        while (m -- )
        {
            int a, b;
            cin >> a >> b;
            n = max(n, a), n = max(n, b);
            g[a].push_back(b);
            g[b].push_back(a);
        }

        for (root = 1; root <= n; root ++ )
            if (!dfn[root])
                tarjan(root);
            for(int i=1;i<=n;i++)g[i].clear();
            int res = 0;
            ULL num = 1;
            for (int i = 1; i <= dcc_cnt; i ++ )
            {
                int cnt = 0;
                for (int j = 0; j < dcc[i].size(); j ++ )
                    if (cut[dcc[i][j]])
                        cnt ++ ;

                    if (cnt == 0)
                    {
                        if (dcc[i].size() > 1) res += 2, num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
                        else res ++ ;
                    }
                    else if (cnt == 1) res ++, num *= dcc[i].size() - 1;
            }

            printf("Case %d: %d %llu\n", T ++, res, num);
    }

    return 0;
}