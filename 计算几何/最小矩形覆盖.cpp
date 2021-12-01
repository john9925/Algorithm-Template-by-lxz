/*
 *
 * 已知平面上不共线的一组点的坐标，求覆盖这组点的面积最小的矩形。
输出矩形的面积和四个顶点的坐标。
输入格式
第一行包含一个整数 n，表示点的数量。
接下来 n 行，每行包含两个用空格隔开的浮点数，表示一个点的 x 坐标和 y 坐标。
不用科学计数法，但如果小数部分为 0，则可以写成整数。
输出格式
共 5 行，第 1 行输出一个浮点数，表示所求得的覆盖输入点集的最小矩形的面积。
接下来 4 行，每行包含两个用空格隔开的浮点数，表示所求矩形的一个顶点的 x 坐标和 y 坐标。
先输出 y 坐标最小的顶点的 x,y 坐标，如果有两个点的 y 坐标同时达到最小，则先输出 x 坐标较小者的 x,y 坐标。
然后，按照逆时针的顺序输出其他三个顶点的坐标。
不用科学计数法，精确到小数点后 5 位，后面的 0 不可省略。
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 50010;
const double eps = 1e-12, INF = 1e20;
const double PI = acos(-1);

int n;
PDD q[N];
PDD ans[N];
double min_area = INF;
int stk[N], top;
bool used[N];

int sign(double x)
{
    if (fabs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}

int dcmp(double x, double y)
{
    if (fabs(x - y) < eps) return 0;
    if (x < y) return -1;
    return 1;
}

PDD operator+ (PDD a, PDD b)
{
    return {a.x + b.x, a.y + b.y};
}

PDD operator- (PDD a, PDD b)
{
    return {a.x - b.x, a.y - b.y};
}

PDD operator* (PDD a, double t)
{
    return {a.x * t, a.y * t};
}

PDD operator/ (PDD a, double t)
{
    return {a.x / t, a.y / t};
}

double operator* (PDD a, PDD b)
{
    return a.x * b.y - a.y * b.x;
}

double operator& (PDD a, PDD b)
{
    return a.x * b.x + a.y * b.y;
}

double area(PDD a, PDD b, PDD c)
{
    return (b - a) * (c - a);
}

double get_len(PDD a)
{
    return sqrt(a & a);
}

double project(PDD a, PDD b, PDD c)
{
    return ((b - a) & (c - a)) / get_len(b - a);
}

PDD norm(PDD a)
{
    return a / get_len(a);
}

PDD rotate(PDD a, double b)
{
    return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

void get_convex()
{
    sort(q, q + n);
    for (int i = 0; i < n; i ++ )
    {
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            used[stk[ -- top]] = false;
        stk[top ++ ] = i;
        used[i] = true;
    }
    used[0] = false;
    for (int i = n - 1; i >= 0; i -- )
    {
        if (used[i]) continue;
        while (top >= 2 && sign(area(q[stk[top - 2]], q[stk[top - 1]], q[i])) >= 0)
            top -- ;
        stk[top ++ ] = i;
    }
    reverse(stk, stk + top);
    top -- ;
}

void rotating_calipers()
{
    for (int i = 0, a = 2, b = 1, c = 2; i < top; i ++ )
    {
        auto d = q[stk[i]], e = q[stk[i + 1]];
        while (dcmp(area(d, e, q[stk[a]]), area(d, e, q[stk[a + 1]])) < 0) a = (a + 1) % top;
        while (dcmp(project(d, e, q[stk[b]]), project(d, e, q[stk[b + 1]])) < 0) b = (b + 1) % top;
        if (!i) c = a;
        while (dcmp(project(d, e, q[stk[c]]), project(d, e, q[stk[c + 1]])) > 0) c = (c + 1) % top;
        auto x = q[stk[a]], y = q[stk[b]], z = q[stk[c]];
        auto h = area(d, e, x) / get_len(e - d);
        auto w = ((y - z) & (e - d)) / get_len(e - d);
        if (h * w < min_area)
        {
            min_area = h * w;
            ans[0] = d + norm(e - d) * project(d, e, y);
            ans[3] = d + norm(e - d) * project(d, e, z);
            auto u = norm(rotate(e - d, -PI / 2));
            ans[1] = ans[0] + u * h;
            ans[2] = ans[3] + u * h;
        }
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%lf%lf", &q[i].x, &q[i].y);
    get_convex();
    rotating_calipers();

    int k = 0;
    for (int i = 1; i < 4; i ++ )
        if (dcmp(ans[i].y, ans[k].y) < 0 || !dcmp(ans[i].y, ans[k].y) && dcmp(ans[i].x, ans[k].x))
            k = i;

        printf("%.5lf\n", min_area);
        for (int i = 0; i < 4; i ++, k ++ )
        {
            auto x = ans[k % 4].x, y = ans[k % 4].y;
            if (!sign(x)) x = 0;
            if (!sign(y)) y = 0;
            printf("%.5lf %.5lf\n", x, y);
        }

        return 0;
}