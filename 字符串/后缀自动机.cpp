/*
后缀自动机
图中每个点就是一个等价类，这些点形成的串（从原点到这个点的路径）都有相同的endpos集合。任意两个点的串没有任何交集。每个点对应的串一定都是最长串的连续后缀。每个点的最短串删掉头部的一个字符后，连条绿边到短串剩下的对应串的点。

当前等价类是p，则该等价类对应串的公共后缀是fa[p]的len，该等价类最短串是fa[p].len+1
如下是枚举每个等价类，每次相当于枚举一堆子串，每次枚举知道这堆子串出现了fi次，且其中最长的是node[u].len，最短的是node[node[u].fa].len+1。相当于枚举出所有子串

多组
idx=ans=0;
tot=1,last=1;
memset(h, -1, sizeof h);
memset(node,0,sizeof node);
memset(f,0,sizeof f);//！！！！
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 2000010;//节点数量是长度的两倍！！

int tot = 1, last = 1;
struct Node
        {
    int len, fa;//len表示当前状态最大串的长度，fa是绿边。
    int ch[26];//蓝边
        }node[N];
char str[N];
LL f[N], ans;//f[i]表示i这类（endpos集合）内的元素数。所以枚举所有集合就是枚举所有子串，如果f[i]>1说明这个集合的串出现次数都大于1。然后用f[i]*len
int h[N], e[N], ne[N], idx;

void extend(int c)
{
    int p = last, np = last = ++ tot;
    f[tot] = 1;//这个位置前的前缀记录一下
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    if (!p) node[np].fa = 1;
    else
    {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else
        {
            int nq = ++ tot;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        dfs(e[i]);
        f[u] += f[e[i]];
    }
    if (f[u] > 1) ans = max(ans, f[u] * node[u].len);
}

int main()
{
    scanf("%s", str);
    for (int i = 0; str[i]; i ++ ) extend(str[i] - 'a');
    memset(h, -1, sizeof h);
    for (int i = 2; i <= tot; i ++ ) add(node[i].fa, i);
    dfs(1);
    printf("%lld\n", ans);

    return 0;
}