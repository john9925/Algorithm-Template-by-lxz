/*模拟退火  求最大值最小值*/
#include<bits/stdc++.h>
using namespace std;
const int N=105;
#define x first
#define y second
typedef pair<double,double> pdd;
int n;
pdd q[N];
double ans=1e8;

double rand(double l,double r)//得到l-r之间的随机数
{
    return (double)rand()/RAND_MAX*(r-l)+l;
}
double cal(pdd a,pdd b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double calc(pdd x)
{
    double res=0;
    for(int i=0;i<n;i++)
    {
        res+=cal(q[i],x);
    }
    ans=min(ans,res);
    return res;
}
void simulate_anneal()
{
    pdd cur(rand(0,10000),rand(0,10000));
    for(double t=1e4;t>1e-4;t*=0.99)//初温1e4 终止温1e-4 衰减系数0.99(可以看情况改，越大循环次数越多),t步长
        {
        pdd np(rand(cur.x-t,cur.x+t),rand(cur.y-t,cur.y+t));
        double dt=calc(np)-calc(cur);
        if(exp(-dt/t)>rand(0,1))cur=np;
        /*这样写恰好就是我们想走的
        1.dt<0时，说明新点距离变小，结果更好，exp(>0)>1>rand(0,1)一定跳到新点
        2.dt>0时，说明新点距离变大，结果变差。0<exp(<0)<1且dt越大(新点结果很差) 整个exp越小，跳的概率越低。
         */
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)cin>>q[i].x>>q[i].y;
    for(int i=0;i<n;i++)simulate_anneal();//迭代100次模拟退火
    printf("%.0lf",ans);
    return 0;
}