//2020/10/18
//RMQ也叫st表，解决区间最值
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,M=18;
int w[N],f[N][M],n,q;//f代表从i开始2^j长度（点）的区间
void ini()
{
    for(int j=0;j<M;j++)//类似区间dp，要从小的长度开始
        for(int i=1;i+(1<<j)-1<=n;i++)
        {
            if(!j)f[i][j]=w[i];//j=0，即长度为1，只有一个点
            else f[i][j]=max(f[i][j-1],f[i+(1<<j-1)][j-1]);//区间平分。
        }

}
int query(int l,int r)
{
    int t=r-l+1;
    k=log2(t);//2^k再乘2则必定大于l-r长度
    return max(f[l][k],f[r-(1<<k)+1][k]);//分为l前缀，r后缀两个区间[l,l-2^k],[r-2^k+1,r]
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>w[i];
    cin>>q;
    ini();
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        cout<<query(l,r)<<endl;
    }
    return 0;
}