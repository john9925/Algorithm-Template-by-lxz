/*
后缀数组
多组，且可以求lcp（i，j），即querymin（i+1，j），这里i，j都是排名
Sa[i] 排名第i的是哪个后缀
Rank[i]第i个后缀的排名
Height[i] sa【i】和sa【i-1】的最长公共前缀
Lcp(i,j)=min(lcp(i,i+1,)......lcp(j-1,j).
*/
#include<bits/stdc++.h>

using namespace std;

const int N = 5005,M=15;

int n, m;
char s[N];
int sa[N], x[N], y[N], c[N], rk[N], height[N],dp[N],lg[N],f2[N][M];

void get_sa()
{
    for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        int num = 0;
        for (int i = n - k + 1; i <= n; i ++ ) y[ ++ num] = i;
        for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k;
            for (int i = 1; i <= m; i ++ ) c[i] = 0;
            for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
            for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
            for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0;
            swap(x, y);
            x[sa[1]] = 1, num = 1;
            for (int i = 2; i <= n; i ++ )
                x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
            if (num == n) break;
            m = num;
    }
}

void get_height()
{
    for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
    for (int i = 1, k = 0; i <= n; i ++ )
    {
        if (rk[i] == 1) continue;
        if (k) k -- ;
        int j = sa[rk[i] - 1];
        while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
        height[rk[i]] = k;
    }
}
void inimin()
{
    for(int j=0;j<M;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
        {
            if(!j)f2[i][j]=height[i];
            else f2[i][j]=min(f2[i][j-1],f2[i+(1<<j-1)][j-1]);
        }

}
int querymin(int l,int r)
{
    // if(l>r)swap(l,r);
    // if(max(l,r)>n)return 0;
    // 求lcp时 （i+1，j）因为左边加了1，可能超过n。
    int t=r-l+1,k;
    k=lg[t];
    return min(f2[l][k],f2[r-(1<<k)+1][k]);
}
int main()
{
    for(int i=2;i<N;i++)lg[i]=lg[i/2]+1;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        scanf("%s", s + 1);
        m = 122;
        for(int i=0;i<=max(n,122);i++)
        {
            sa[i]=x[i]=y[i]=c[i]=rk[i]=height[i]=0;
        }
        get_sa();
        get_height();
        inimin();
    }
    return 0;
}