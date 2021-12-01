/*
01可持久化trie，求区间L-R 与C的最大异或
你需要找到一个位置 p，满足 l≤p≤r，使得：a[p] xor a[p+1] xor … xor a[N] xor x 最大，输出这个最大值。
第R个版本存的就是1-R所有数的信息
*/
#include<bits/stdc++.h>
using namespace std;
const int N=6e5+10,M=25*N;
int s[N];
int tr[M][2],max_id[M];//maxid代表结点idx的子树（的数中）对应最大的下标i
int root[N],idx;//root代表第i个数的结点idx
void insert(int k,int p,int q)//第i个数，上一个版本，当前版本
{
    for(int i=23;i>=0;i--)
    {
        int v=s[k]>>i&1;
        if(p)tr[q][v^1]=tr[p][v^1];//复制除了当前v以外的信息，因为当前的都是新开结点
        //上面都一样，复制过来以后就可以从新版本把前面全部都走一遍
        tr[q][v]=++idx;
        max_id[idx]=k;
        p=tr[p][v],q=tr[q][v];
    }
}
int query(int p,int l,int c)
{
    for(int i=23;i>=0;i--)
    {
        int v=c>>i&1;
        if(max_id[tr[p][v^1]]>=l)p=tr[p][v^1];//如果相反的方向的子树最大下标>=l就走过去（因为可以取到那个数）
        else p=tr[p][v];
    }
    return c^s[max_id[p]];
}
int main()
{
    max_id[0]=-1;//假如不存在tr[p][v^1]这个结点。则结点为0.而l可能取到0，所以设为-1
    root[0]=++idx;//在trie树中0既是根节点，又是空节点，意义非凡，得先空出来。
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        s[i]=s[i-1]^x;
        root[i]=++idx;
        insert(i,root[i-1],root[i]);
    }
    char op[2];
    while(m--)
    {
        scanf("%s",&op);
        if(*op=='A')//序列末尾添加一个元素
        {
            int x;
            scanf("%d",&x);
            n++;
            root[n]=++idx;
            s[n]=s[n-1]^x;
            insert(n,root[n-1],root[n]);
        }
        else//你需要找到一个位置 p，满足 l≤p≤r，使得：a[p] xor a[p+1] xor … xor a[N] xor x 最大，输出这个最大值。
        {
            int l,r,x;
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",query(root[r-1],l-1,s[n]^x));
        }
    }
    return 0;
}