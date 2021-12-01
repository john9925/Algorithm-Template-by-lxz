/*
跨区间写的时候，即pushup，切记
u.l=L.l,u.r=R.r;
u.pre=L.pre,u.suf=R.suf;之类的，因为u可能啥都没有，要先继承
 */
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
int a[N];
struct node
        {
    int l,r;
    int tmax,lmax,rmax,sum;//最大子段和，最大前缀和，最大后缀和，区间和
        }tr[4*N];
inline void pushup(node &u,node &l,node &r)
{
    u.sum=l.sum+r.sum;
    u.lmax=max(l.lmax,l.sum+r.lmax);
    u.rmax=max(r.rmax,r.sum+l.rmax);
    u.tmax=max(l.tmax,max(r.tmax,l.rmax+r.lmax));
}
inline void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}
void build(int u,int l,int r)
{
    tr[u]={l,r};
    if(l==r)
    {
        tr[u]={l,r,a[l],a[l],a[l],a[l]};
        return ;
    }
    int mid=l+r>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    pushup(u);
}
void update(int u,int x,int v)
{
    if(tr[u].l==x&&tr[u].r==x)
    {
        tr[u]={x,x,v,v,v,v};
        return ;
    }
    int mid=tr[u].l+tr[u].r>>1;
    if(x<=mid)update(u<<1,x,v);
    else update(u<<1|1,x,v);
    pushup(u);
}
node query(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        return tr[u];
    }
    int mid=tr[u].l+tr[u].r>>1;
    if(r<=mid)return query(u<<1,l,r);//查询区间在当前区间mid左侧
    else if(l>mid)return query(u<<1|1,l,r);//查询区间在当前区间mid右侧
    else//查询区间跨过mid，则要pushup
    {
        auto left=query(u<<1,l,r);
        auto right=query(u<<1|1,l,r);
        node tree;
        pushup(tree,left,right);
        return tree;
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    build(1,1,n);
    while(m--)
    {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1)
        {
            if(x>y)swap(x,y);
            printf("%d\n",query(1,x,y).tmax);
        }
        else
        {
            update(1,x,y);
        }
    }
    return 0;
}