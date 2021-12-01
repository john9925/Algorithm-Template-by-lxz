struct DSU
        {
    struct Stack
            {
        int u, v, rk;
            } st[maxn];
    int fa[maxn], rk[maxn], top;
    inline void init()
    {
        top = 0;
        for(int i=1; i<=n; i++)
            fa[i] = i, rk[i] = 0;
    }
    inline int find(int x)
    {
        return x == fa[x] ? x : find(fa[x]);
    }
    inline bool unite(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)
            return 0;
        if(rk[fu] > rk[fv])
            swap(u, v), swap(fu, fv);
        st[++top] = {fu, fv, rk[fv]};
        fa[fu] = fv, rk[fv] += rk[fu] == rk[fv];
        return 1;
    }
    inline void undo(int k)//撤回k次
    {
        while(k--)
        {
            Stack &now = st[top--];
            int u = now.u, v = now.v;
            fa[u] = u, rk[v] = now.rk;
        }
    }
}dd;