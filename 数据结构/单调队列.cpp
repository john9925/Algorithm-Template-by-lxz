#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,k,q[N],a[N];
int main()
{
    cin>>n>>k;
    for(int i=0;i<n;i++)cin>>a[i];
    int hh=0,tt=-1;
    for(int i=0;i<n;i++)//求窗口最小值
    {
        if(hh<=tt&&q[hh]<i-k+1)hh++;//队头下标已经不在窗口内
        while(hh<=tt&&a[q[tt]]>=a[i])tt--;
        q[++tt]=i;
        if(i>=k-1)printf("%d ",a[q[hh]]);
    }
    puts("");
    hh=0,tt=-1;
    for(int i=0;i<n;i++)//求窗口最大值
    {
        if(hh<=tt&&q[hh]<i-k+1)hh++;
        while(hh<=tt&&a[q[tt]]<=a[i])tt--;
        q[++tt]=i;
        if(i>=k-1)printf("%d ",a[q[hh]]);
    }
    return 0;
}
