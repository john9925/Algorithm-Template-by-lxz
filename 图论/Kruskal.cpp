//2020/8/17
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct edge
{
    int a,b,z;
    bool operator < (const edge &T) const {
        return z < T.z;
    }
}e[N];
int fa[N],cnt,res;
int find(int x)
{
    if(x!=fa[x])return fa[x]=find(fa[x]);
    return x;
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        e[i]={a,b,c};
    }
    sort(e,e+m);
    for(int i=0;i<m;i++)
    {
        int a=e[i].a,b=e[i].b,c=e[i].z;
        a=find(a),b=find(b);
        if(a!=b)
        {
            fa[a]=b;
            //cout<<c<<endl;
            res+=c;
            cnt++;
        }
    }
    if(cnt<n-1)puts("impossible");
    else cout<<res;
}
