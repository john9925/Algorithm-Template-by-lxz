#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;//相当于模2^64
const int N=1e5+10,P=131;//P是经验值，一般取131或13331，然后模2^64
ull p[N],h[N];//p存储P的i次方,h是前缀哈希
char s[N];
ull get(int l,int r)
{
    return h[r]-h[l-1]*p[r-l+1];
    /*
    h[r]最高位的次幂比h[l-1]高
    所以要把h[l-1]的次幂乘上去
    然后做差，把高位的部分抵掉
    比如
    h(abcd)=a*p^3+b*p^2+c*p^1+d*p^0
    h(ab)=a*p^1+b*p^0
    l=3,r=4
    h(cd)=c*p^1+d*P^0=h(abcd)-h(ab)*P^(2)
    */
}
int main()
{
    int m,n;
    cin>>m>>n;
    cin>>s+1;
    p[0]=1;
    for(int i=1;i<=m;i++)
    {
        p[i]=p[i-1]*P;
        h[i]=h[i-1]*P+s[i];
        /*
        例子
        abcd
        H(a)=a*P^(0)
        H(ab)=a*P^1+b*P^0=H(a)*P+b
        */
    }
    while(n--)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(get(a,b)==get(c,d))puts("Yes");
        else puts("No");
    }
}
//判断l-r是否是回文
ull getl(int l,int r)//从左往右的哈希
{
    return hl[r]-hl[l-1]*p[r-l+1];
}
ull getr(int l,int r)//从右往左的哈希
{
    return hr[l]-hr[r+1]*p[r-l+1];
}
bool check(int l,int r)
{
    return getl(l,r)==getr(l,r);
}

for(int i=1;i<=n;i++)
{
    hl[i]=hl[i-1]*P+s[i];
    p[i]=p[i-1]*P;
}
for(int i=n;i>=1;i--)
{
    hr[i]=hr[i+1]*P+s[i];
}
