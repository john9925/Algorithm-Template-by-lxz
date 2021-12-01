
#define IO ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)

//得到l-r之间的整数随机数
#define RAND mt19937 rng(chrono::steady_clock::now().time_since_epoch().count())
#define grand(l,r) uniform_int_distribution<int>(l,r)(rng)

使用方法
RAND;
int x=rand(l,r);

double rand(double l,double r)//得到l-r之间的浮点随机数
{
    return (double)rand()/RAND_MAX*(r-l)+l;
}