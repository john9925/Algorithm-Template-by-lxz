//结点存的是编号，边上是字母，代表方向    
#include<bits/stdc++.h>
using namespace std;
const int N=2e4+10;
int son[N][26],cnt[N],idx;//cnt 表示以。。结尾的个数
char str[N];
void insert(char s[])
{
    int p=0;
    for(int i=0;s[i];i++)
    {
        int u=s[i]-'a';
        if(!son[p][u])son[p][u]=++idx;
        p=son[p][u];
    }
    cnt[p]++;
}
int query(char s[])
{
    int p=0;
    for(int i=0;s[i];i++)
    {
        int u=s[i]-'a';
        if(!son[p][u])return 0;
        p=son[p][u];
    }
    return cnt[p];
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        char x;
        cin>>x>>str;
        if(x=='I')insert(str);
        else printf("%d\n",query(str));
    }
}