/*
三维凸包
1. 三维向量表示(x, y, z)
2. 向量加减法、数乘运算，与二维相同
3. 模长 |A| = sqrt(x * x + y * y + z * z)
4. 点积
(1) 几何意义：A·B = |A| * |B| * cos(C)
(2) 代数求解：(x1, y1, z1) · (x2, y2, z2) = (x1x2, y1y2, z1z2);
5. 叉积
(1) 几何意义：AxB = |A| * |B| * sin(C)，方向：右手定则
(2) 代数求解：AxB = (y1z2 - z1y2, z1x2 - x1z2, x1y2 - x2y1)
6. 如何求平面法向量
任取平面上两个不共线的向量A、B：AxB
7. 判断点D是否在平面里
任取平面上两个不共线的向量A、B：先求法向量C = AxB，然后求平面上任意一点到D的向量E与C的点积，判断点积是否为0。
8. 求点D到平面的距离
任取平面上两个不共线的向量A、B：先求法向量C = AxB。然后求平面上任意一点到D的向量E在C上的投影长度即可。即：E·C / |C|
9. 多面体欧拉定理
顶点数 - 棱长数 + 表面数 = 2
10. 三维凸包
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 210;
const double eps = 1e-10;

int n, m;
bool g[N][N];

double rand_eps()
{
    return ((double)rand() / RAND_MAX - 0.5) * eps;
}

struct Point
        {
    double x, y, z;
    void shake()
    {
        x += rand_eps(), y += rand_eps(), z += rand_eps();
    }
    Point operator- (Point t)
    {
        return {x - t.x, y - t.y, z - t.z};
    }
    double operator& (Point t)
    {
        return x * t.x + y * t.y + z * t.z;
    }
    Point operator* (Point t)
    {
        return {y * t.z - t.y * z, z * t.x - x * t.z, x * t.y - y * t.x};
    }
    double len()
    {
        return sqrt(x * x + y * y + z * z);
    }
        }q[N];
struct Plane
        {
    int v[3];
    Point norm()  // 法向量
    {
        return (q[v[1]] - q[v[0]]) * (q[v[2]] - q[v[0]]);
    }
    double area()  // 求面积
    {
        return norm().len() / 2;
    }
    bool above(Point a)
    {
        return ((a - q[v[0]]) & norm()) >= 0;
    }
        }plane[N], np[N];

void get_convex_3d()
{
    plane[m ++ ] = {0, 1, 2};
    plane[m ++ ] = {2, 1, 0};
    for (int i = 3; i < n; i ++ )
    {
        int cnt = 0;
        for (int j = 0; j < m; j ++ )
        {
            bool t = plane[j].above(q[i]);
            if (!t) np[cnt ++ ] = plane[j];
            for (int k = 0; k < 3; k ++ )
                g[plane[j].v[k]][plane[j].v[(k + 1) % 3]] = t;
        }
        for (int j = 0; j < m; j ++ )
            for (int k = 0; k < 3; k ++ )
            {
                int a = plane[j].v[k], b = plane[j].v[(k + 1) % 3];
                if (g[a][b] && !g[b][a])
                    np[cnt ++ ] = {a, b, i};
            }
        m = cnt;
            for (int j = 0; j < m; j ++ ) plane[j] = np[j];
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ )
    {
        scanf("%lf%lf%lf", &q[i].x, &q[i].y, &q[i].z);
        q[i].shake();
    }
    get_convex_3d();

    double res = 0;
    for (int i = 0; i < m; i ++ )
        res += plane[i].area();
    printf("%lf\n", res);
    return 0;
}