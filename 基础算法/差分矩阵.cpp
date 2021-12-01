//2020/8/3
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,m,q,a[N][N],b[N][N];//b数组为变化量
int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }
    }
    while(q--)
    {
        int x1,y1,x2,y2,c;
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&c);
        b[x1][y1]+=c;//x1,y1右下角的矩阵全部加上c
        b[x2+1][y1]-=c;
        b[x1][y2+1]-=c;
        b[x2+1][y2+1]+=c;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            //如下操作i，j前面的b已经变成前缀和了
            b[i][j]+=b[i-1][j]+b[i][j-1]-b[i-1][j-1];//差分矩阵复原为前缀和(对b做前缀和（1，1）-（i，j)的和
            printf("%d ",b[i][j]+a[i][j]);//原来的加上差值即可
        }
        puts("");
    }

}
