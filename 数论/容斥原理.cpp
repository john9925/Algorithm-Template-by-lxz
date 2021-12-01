//容斥原理 复杂度O(m∗2^m)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int p[20];
int main()
{
    ll n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++)cin>>p[i];
    ll res=0;
    for(int i=1;i<1<<m;i++)//枚举每一种情况，选一个，选两个.....
    {
        ll t=1,cnt=0;
        for(int j=0;j<m;j++)
        {
            if(i>>j&1)
            {
                if(p[j]*t>n)//如果选的数乘起来比n大
                {
                    t=-1;
                    break;
                }
                t*=p[j];
                cnt++;
            }
        }
        if(t!=-1)
        {
            if(cnt%2)res+=n/t;//奇数时是加，偶数是-
            else res-=n/t;
        }
    }
    cout<<res;
    return 0;
}
