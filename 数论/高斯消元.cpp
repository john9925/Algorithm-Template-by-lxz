#include<bits/stdc++.h>
using namespace std;
const int N=105;
double a[N][N];
const double eps=1e-6;
int n;
int gauss()
{
    int r,c;//row行。cow列
    for(r=0,c=0;c<n;c++)//一列一列处理
    {
        int t=r;//找到当前列,绝对值最大的一个数所在的行
        for(int i=r;i<n;i++)
        {
            if(fabs(a[i][c])>fabs(a[t][c]))t=i;
        }
        if (fabs(a[t][c]) < eps) continue;// 如果当前这一列的最大数都是 0 ，那么所有数都是 0，就没必要去算了，因为它的约束方程，可能在上面几行
        for(int i=c;i<=n;i++)swap(a[t][i],a[r][i]);//把当前这行换到最上面去（r行）不是第0行
        for(int i=n;i>=c;i--)a[r][i]/=a[r][c];//从后往前
        //交换好后，这行到r行去了，把r行第一个数变成1。从后往前刚好（避免第一个数先变成1）。把这行每个数都除第一个数
        for(int i=r+1;i<n;i++)
        {
            /*      c       j
            r:      1 x x x x
            r+1:    k s x t s
            */
            for(int j=n;j>=c;j--)//为了把r行下面每一行第一个数变成1，每一行从后往前，
            {
                a[i][j]-=a[r][j]*a[i][c];
            }
        }
        r++;
    }
    if(r<n)
    {
        /*  r~n-1的=左边都是0
            1 x x s
              1 x s
                0 s

        */
        for(int i=r;i<n;i++)
        {
            if(fabs(a[i][n]>eps))return 2;//无解。因为出现了0==一个数
        }
        return 1;//出现0==0 无限解
    }
    //有唯一解，有n个方程组n个未知数
    /*
    1 0 0 0 x
      1 0 0 x
        1 0 x
          1 x
    处理成这种效果
    */
    for(int i=n-1;i>=0;i--)
        for(int j=i+1;j<n;j++)a[i][n]-=a[j][n]*a[i][j];
    return 0;
}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n+1;j++)cin>>a[i][j];
    int t=gauss();
    if(t==0)for(int i=0;i<n;i++)printf("%.2lf\n",a[i][n]);
    else if(t==1)puts("Infinite group solutions");
    else puts("No solution");
    return 0;
}
