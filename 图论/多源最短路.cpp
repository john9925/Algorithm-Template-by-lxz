#include<bits/stdc++.h>
using namespace std;
const int N=205;
int a[N][N];
#define inf 0x3f3f3f3f
int main()
{
    int n,m,q;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)a[i][j]=0;
            else a[i][j]=inf;
        }
    }
    while(m--)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if(z<a[x][y])a[x][y]=z;
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(a[i][j]>a[i][k]+a[k][j])a[i][j]=a[i][k]+a[k][j];
            }
        }
    }
    while(q--)
    {
        int u,v;
        cin>>u>>v;
        if(a[u][v]>inf/2)puts("impossible");
        else cout<<a[u][v]<<endl;
    }
}