/*
主席树。可持久化权值线段树。权值即比如权值在1-4区间的数个数。6 4 2 3 4 则权值在1-4中有4个数。
1-R版本中权值在某区间的个数。用类似前缀和可以求任意一段区间
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10, M = 1e4 + 10;
int n, m;
int a[N], t[N];
struct node {
    int l, r;//存左子树和右子树的结点idx下标。
    int cnt;//区间中有几个数出现了。
} tr[N * 4 + 17 * N];//初始就要N*4，后续插入每个数最多logn，插入n次。
int root[N], idx;//每个版本的根节点idx
int build(int l, int r) {
    int p = ++idx;
    if (l == r)return p;
    int mid = l + r >> 1;
    tr[p].l = build(l, mid), tr[p].r = build(mid + 1, r);
    return p;
}

int insert(int p, int l, int r, int x) {
    int q = ++idx;
    tr[q] = tr[p];
    if (l == r) {
        tr[q].cnt++;
        return q;
    }
    int mid = l + r >> 1;
    if (x <= mid)tr[q].l = insert(tr[p].l, l, mid, x);//新的东西要新开结点，其他的全部复制过来
    else tr[q].r = insert(tr[p].r, mid + 1, r, x);
    tr[q].cnt = tr[tr[q].l].cnt + tr[tr[q].r].cnt;
    return q;
}

int query(int q, int p, int l, int r, int k)//返回离散化后下标
{
    if (l == r) return r;
    int cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;//两个版本之间的区间。在左(1~mid)区间范围内数的个数
    int mid = l + r >> 1;
    if (k <= cnt) return query(tr[q].l, tr[p].l, l, mid, k);
    else return query(tr[q].r, tr[p].r, mid + 1, r, k - cnt);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        t[i] = a[i];
    }
    sort(t + 1, t + 1 + n);
    int len = unique(t + 1, t + 1 + n) - (t + 1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(t + 1, t + 1 + n, a[i]) - t;
    root[0] = build(1, len);//似乎不要也可以
    for (int i = 1; i <= n; i++)
        root[i] = insert(root[i - 1], 1, len, a[i]);
    while (m--) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", t[query(root[r], root[l - 1], 1, len, k)]);
    }
    return 0;
}