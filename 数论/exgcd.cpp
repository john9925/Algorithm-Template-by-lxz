//2020/7/25
#include<bits/stdc++.h>
using namespace std;
int exgcd(int a,int b,int &x,int &y)
{
    if(!b)
    {
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);//带入得可得ax+b（y-a/bx)=d，a的系数x不变
    y-=a/b*x;
    return d;
}

int main()
{
    int n;
    cin>>n;
    while(n--)
    {
        int a,b,x,y;
        scanf("%d %d",&a,&b);
        exgcd(a,b,x,y);
        printf("%d %d\n",x,y);

    }
    return 0;
}
