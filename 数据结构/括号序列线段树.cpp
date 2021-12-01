#include<bits/stdc++.h>

using namespace std;
const int maxn=1e6+10;
char c[maxn];
struct in
        {
    int a,b,sum;
    in(){ a=0; b=0; sum=0;}
        }s[maxn<<2];
void read(int &res)
{
    char c=getchar();res=0; for(;c>'9'||c<'0';c=getchar());
    for(;c<='9'&&c>='0';c=getchar()) res=(res<<3)+(res<<1)+c-'0';
}

struct segment_tree
        {
    void pushup(int Now)
    {
        int tmp=min(s[Now<<1].a,s[Now<<1|1].b);
        s[Now].sum=s[Now<<1].sum+s[Now<<1|1].sum+tmp;
        s[Now].a=s[Now<<1].a+s[Now<<1|1].a-tmp;
        s[Now].b=s[Now<<1].b+s[Now<<1|1].b-tmp;
    }
    void build(int Now,int L,int R)
    {
        if(L==R) {
            s[Now].a=(c[L]=='('?1:0);
            s[Now].b=(c[L]==')'?1:0);
            s[Now].sum=0; return ;
        }
        int Mid=(L+R)>>1;
        build(Now<<1,L,Mid);
        build(Now<<1|1,Mid+1,R);
        pushup(Now);
    }
    in query(int Now,int L,int R,int l,int r)
    {
        if(l<=L&&r>=R) return s[Now];
        int Mid=(L+R)>>1; in w,e,res;
        if(l<=Mid) w=query(Now<<1,L,Mid,l,r);
        if(r>Mid) e=query(Now<<1|1,Mid+1,R,l,r);
        res.sum=min(w.a,e.b);
        res.a=w.a+e.a-res.sum;
        res.b=w.b+e.b-res.sum;
        res.sum+=w.sum+e.sum;
        return res;
    }
    void update(int Now,int L,int R,int v,char x)
    {
        if(L==v&&R==v)
        {
            s[Now].a=(x=='('?1:0);
            s[Now].b=(x==')'?1:0);
            s[Now].sum=0;
            return ;
        }
        int mid=L+R>>1;
        if(v<=mid) update(Now<<1,L,mid,v,x);
        if(v>mid) update(Now<<1|1,mid+1,R,v,x);
        pushup(Now);
    }
        }Tree;

int main()
{
    int N,Q,x,y;
    read(N);
    read(Q);
    scanf("%s",c+1);
    Tree.build(1,1,N);

    while(Q--){
        int op;
        read(op),read(x); read(y);
        if(op==2)
        {
            if(2*Tree.query(1,1,N,x,y).sum==y-x+1)puts("Yes");
            else puts("No");
        }
        else
        {
            Tree.update(1,1,N,x,c[y]);
            Tree.update(1,1,N,y,c[x]);
            swap(c[x],c[y]);
        }
    }
    return 0;
}