//2020/9/2
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
    int l,r;//该节点代表的区间[l~r]
    int v;
}tr[4*N];//某个结点
int m,p;
inline void pushup(int u)
{
    tr[u].v=max(tr[u<<1].v,tr[u<<1|1].v);
}
void build(int u,int l,int r)
{
    tr[u]={l,r};
    if(l==r)return ;
    int mid=l+r>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
int query(int u,int l,int r)
{
    if(tr[u].l>=l&&tr[u].r<=r)return tr[u].v;//当前区间包含于查询区间[l,r]，这样最后肯定是多段区间return
    int mid=tr[u].l+tr[u].r>>1;
    int v=0;
    //与左区间有交集
    if(l<=mid)v=query(u<<1,l,r);//递归区间，查询区间始终是[l,r]
    //与右区间有交集
    if(r>mid)v=max(query(u<<1|1,l,r),v);
    return v;
}
void update(int u,int x,int v)
{
    if(tr[u].l==x&&tr[u].r==x)
    {
        tr[u].v=v;
    }
    else
    {
        int mid=tr[u].l+tr[u].r>>1;
        if(x<=mid)update(u<<1,x,v);
        else update(u<<1|1,x,v);
        pushup(u);
    }

}
int main()
{
    cin>>m>>p;
    build(1,1,m);
    int last=0,n=0;
    while(m--)
    {
        char op[2];
        int x;
        scanf("%s%d",&op,&x);//不能scanf("%c%d")%c连空格回车都会读入,把回车读进去了，除非后面加个getchar
        if(*op=='A')
        {
            update(1,n+1,(x+last)%p);
            n++;
        }
        else
        {
            last=query(1,n-x+1,n);
            printf("%d\n",last);
        }
    }
    return 0;
}