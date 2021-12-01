#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=35;
int f[N][N],pos=0,a[N],x,y,k,b;//f[i][j]表示 当前枚举到第i位，前面已经取了j个1的方案数
int dfs(int pos,int pre,int last,int limit)
//pos当前枚举的位数，pre前面取了多少个1，last上一个数是几，limit当前位取数有没有限制
{
    if(!pos)return pre==k;//枚举完成了，判断边界这个数是否符合要求
    if(last>1)return 0;//如果前一位取了比1大的数，直接不符合要求。
    if(!limit&&f[pos][pre]!=-1)return f[pos][pre];//记忆化
    int up=limit?a[pos]:b;
    int res=0;
    if(up==0)res+=dfs(pos-1,pre,0,1);//当前位最高只能取0，直接进入下一位看
    else if(up)//当前位最高可以取>=1
        {
        res+=dfs(pos-1,pre,0,0);//则当前位取0一定合法
        if(up>1)
        {
            if(pre<k)res+=dfs(pos-1,pre+1,1,0);//当前位取1的话
        }
        else if(up==1)//当前位最高只能取1，那么只能取1了。（取0在前面已经写了）
            {
            if(pre<k)res+=dfs(pos-1,pre+1,1,1);
            }
        }
    if(!limit)f[pos][pre]=res;
    return res;
}
int dp(int n)
{
    if(!n)return 0;
    int pos=0;
    while(n)
    {
        a[++pos]=n%b;
        n/=b;
    }
    return dfs(pos,0,0,1);
}
int main()
{
    memset(f,-1,sizeof f);
    cin>>x>>y>>k>>b;
    cout<<dp(y)-dp(x-1);
    return 0;
}


ll dfs(int pos,ll pre,int lead,int limit)
{
    if(!limit&&!lead&&f[pos].count(pre))return f[pos][pre];
    if(!pos)
    {
        return pre<=k&&!lead;
    }
    int up = limit? a[pos] : 9;
    ll res = 0;
    for(int k = 0; k <= up; k++){
        if(lead)
        {
            if(!k)res  += dfs(pos-1,1,lead,limit && k == up );
            else res  += dfs(pos-1,k,0,limit && k == up );
        }
        else res  += dfs(pos-1,pre*k,0,limit && k == up );
    }
    if(!limit&&!lead)return f[pos][pre]=res;
    return res;
}
ll dp(ll n)
{
    int pos=0;
    while(n)
    {
        a[++pos]=n%10;
        n/=10;
    }
    return dfs(pos,1,1,1);
}

