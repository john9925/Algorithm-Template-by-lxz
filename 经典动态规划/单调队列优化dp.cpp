//输入一个长度为 n 的整数序列，从中找出一段长度不超过 m 的连续子序列，使得子序列中所有数的和最大。
//注意： 子序列的长度至少是 1。
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
typedef long long ll;
ll s[N],q[N];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
        s[i]+=s[i-1];
    }
    int tt=0,hh=0;//t从-1开始，但因为q已经加了个0进去。所以tt++变成0
    //q[0]=0;
    ll res=INT_MIN;
    for(int i=1;i<=n;i++)
    {
        if(i-q[hh]>m)hh++;//j在[i-m,i-1]，因为是前缀和，si-s(j-1);即队列内队头元素下标<i-m就要弹出
        res=max(res,s[i]-s[q[hh]]);
        while(hh<=tt&&s[q[tt]]>=s[i])tt--;
        q[++tt]=i;

    }
    cout<<res;
    return 0;
}
