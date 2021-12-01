/*
给定 n 堆石子以及一个由 k 个不同正整数构成的数字集合 S。
现在有两位玩家轮流操作，每次操作可以从任意一堆石子中拿取石子，每次拿取的石子数量必须包含于集合 S，最后无法进行操作的人视为失败。
问如果两人都采用最优策略，先手是否必胜。
*/
//对每一堆石子求个sg函数，用记忆化，最后将每一堆石子的sg异或。为0则先手必败，否则先手必胜
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int k,n;
int s[N],h[N],f[N];
int sg(int x)
{
    if(f[x]>=0)return f[x];
    unordered_set<int>S;
    for(int i=0;i<k;i++)
    {
        if(x>=s[i])S.insert(sg(x-s[i]));
    }
    for(int i=0;;i++)//当是最后一个点的时候，刚好保证是0
        {
        if(!S.count(i))return f[x]=i;//求mex
        }
}
int main()
{
    cin>>k;
    for(int i=0;i<k;i++)cin>>s[i];
    cin>>n;
    for(int i=0;i<n;i++)cin>>h[i];
    int res=0;
    memset(f,-1,sizeof f);
    for(int i=0;i<n;i++)
    {
        res^=sg(h[i]);
    }
    if(res)puts("Yes");
    else puts("No");
    return 0;
}
