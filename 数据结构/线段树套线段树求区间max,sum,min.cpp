/*
n,m在3000以内可以用。
线段树套线段树，求二维区间最大值，最小值，和。注意每次query都要初始化maxV，minV，sum。
向下是x轴（n），向右是y轴（m）
*/
#define ll long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 1024 + 5;
ll MAX[N << 2][N << 2], minV, maxV,MIN[N<<2][N<<2];//维护最值
ll a[N<<2][N<<2];//初始矩阵
ll SUM[N<<2][N<<2],sumV;//维护求和
int n,m;
void pushupX(int deep, int rt)
{
    MAX[deep][rt] = max(MAX[deep << 1][rt], MAX[deep << 1 | 1][rt]);
    MIN[deep][rt] = min(MIN[deep << 1][rt], MIN[deep << 1 | 1][rt]);
    SUM[deep][rt] = SUM[deep<<1][rt]+SUM[deep<<1|1][rt];
}
void pushupY(int deep, int rt)
{
    MAX[deep][rt] = max(MAX[deep][rt << 1], MAX[deep][rt << 1 | 1]);
    MIN[deep][rt] = min(MIN[deep][rt << 1], MIN[deep][rt << 1 | 1]);
    SUM[deep][rt]=SUM[deep][rt<<1]+SUM[deep][rt<<1|1];
}
void buildY(int ly, int ry, int deep, int rt, int flag)
{
    //y轴范围ly,ry;deep,rt;标记flag
    if (ly == ry){
        if (flag!=-1)
            MAX[deep][rt] = MIN[deep][rt] = SUM[deep][rt] = a[flag][ly];
        else
            pushupX(deep, rt);
        return;
    }
    int mid = (ly + ry) >> 1;
    buildY(ly, mid, deep, rt << 1, flag);
    buildY(mid + 1, ry, deep, rt << 1 | 1, flag);
    pushupY(deep, rt);
}
void buildX(int lx, int rx, int deep)
{
    //建树x轴范围lx,rx;deep
    if (lx == rx){
        buildY(1, m, deep, 1, lx);
        return;
    }
    int mid = (lx + rx) >> 1;
    buildX(lx, mid, deep << 1);
    buildX(mid + 1, rx, deep << 1 | 1);
    buildY(1, m, deep, 1, -1);
}
void updateY(int Y, int val, int ly, int ry, int deep, int rt, int flag)
{
    //单点更新y坐标;更新值val;当前操作y的范围ly,ry;deep,rt;标记flag
    if (ly == ry){
        if (flag) //注意读清楚题意，看是单点修改值还是单点加值
            MAX[deep][rt] = MIN[deep][rt] = SUM[deep][rt] = val;
        else pushupX(deep, rt);
        return;
    }
    int mid = (ly + ry) >> 1;
    if (Y <= mid)
        updateY(Y, val, ly, mid, deep, rt << 1, flag);
    else
        updateY(Y, val, mid + 1, ry, deep, rt << 1 | 1, flag);
    pushupY(deep, rt);
}
void updateX(int X, int Y, int val, int lx, int rx, int deep)
{
    //单点更新范围x,y;更新值val;当前操作x的范围lx,rx;deep
    if (lx == rx){
        updateY(Y, val, 1, m, deep, 1, 1);
        return;
    }
    int mid = (lx + rx) >> 1;
    if (X <= mid)
        updateX(X, Y, val, lx, mid, deep << 1);
    else
        updateX(X, Y, val, mid + 1, rx, deep << 1 | 1);
    updateY(Y, val, 1, m, deep, 1, 0);
}
void queryY(int Yl, int Yr, int ly, int ry, int deep, int rt)
{
    //询问区间y轴范围y1,y2;当前操作y的范围ly,ry;deep,rt
    if (Yl <= ly && ry <= Yr)
    {
        minV = min(MIN[deep][rt], minV);
        maxV = max(MAX[deep][rt], maxV);
        sumV += SUM[deep][rt];
        return;
    }
    int mid = (ly + ry) >> 1;
    if (Yl <= mid)
        queryY(Yl, Yr, ly, mid, deep, rt << 1);
    if (mid < Yr)
        queryY(Yl, Yr, mid + 1, ry, deep, rt << 1 | 1);
}
void queryX(int Xl, int Xr, int Yl, int Yr, int lx, int rx, int rt)
{
    //询问区间范围x1,x2,y1,y2;当前操作x的范围lx,rx;rt
    if (Xl <= lx && rx <= Xr){
        queryY(Yl, Yr, 1, m, rt, 1);
        return;
    }
    int mid = (lx + rx) >> 1;
    if (Xl <= mid)
        queryX(Xl, Xr, Yl, Yr, lx, mid, rt << 1);
    if (mid < Xr)
        queryX(Xl, Xr, Yl, Yr, mid + 1, rx, rt << 1 | 1);
}
ll w[N][N],sum[N][N];
int main()
{
    scanf("%d%d",&n,&m);
    int h1,w1,h2,w2;
    cin>>h1>>w1>>h2>>w2;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            scanf("%lld",&w[i][j]);
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+w[i][j];
        }
    for(int i=min(h2,h1);i<=n;i++)
        for(int j=min(w2,w1);j<=m;j++)
        {
            a[i][j]=sum[i][j]-sum[i-min(h2,h1)][j]-sum[i][j-min(w2,w1)]+sum[i-min(h2,h1)][j-min(w1,w2)];
        }
    buildX(1,n,1);
        ll ans=0;
        for(int i=h1;i<=n;i++)
            for(int j=w1;j<=m;j++)
            {
                maxV=0;
                int x=i-h1+min(h1,h2),y=j-w1+min(w1,w2);
                queryX(x,i,y,j,1,n,1);//填入x1，x2,y1,y2注意x1<=x2 y1<=y2
                ll now=sum[i][j]-sum[i-h1][j]-sum[i][j-w1]+sum[i-h1][j-w1];
                ans=max(ans,now-maxV);
            }
        cout<<ans;
            return 0;
}