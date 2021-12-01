/*
 * 给定n，n行给出三角形顶点
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>

#define x first
#define y second

using namespace std;

typedef pair<double, double> PDD;
const int N = 110;
const double eps = 1e-8, INF = 1e6;

int n;
PDD tr[N][3];
PDD q[N];

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

double operator* (PDD a, PDD b)
{
    return a.x * b.y - a.y * b.x;
}

double operator& (PDD a, PDD b)
{
    return a.x * b.x + a.y * b.y;
}

bool on_segment(PDD p, PDD a, PDD b)
{
    return sign((p - a) & (p - b)) <= 0;
}

PDD get_line_intersection(PDD p, PDD v, PDD q, PDD w)
{
    if (!sign(v * w)) return {INF, INF};
    auto u = p - q;
    auto t = w * u / (v * w);
    auto o = p + v * t;
    if (!on_segment(o, p, p + v) || !on_segment(o, q, q + w))
        return {INF, INF};
    return o;
}

double line_area(double a, int side)
{
    int cnt = 0;
    for (int i = 0; i < n; i ++ )
    {
        auto t = tr[i];
        if (dcmp(t[0].x, a) > 0 || dcmp(t[2].x, a) < 0) continue;
        if (!dcmp(t[0].x, a) && !dcmp(t[1].x, a))
        {
            if (side) q[cnt ++ ] = {t[0].y, t[1].y};
        }
        else if (!dcmp(t[2].x, a) && !dcmp(t[1].x, a))
        {
            if (!side) q[cnt ++ ] = {t[2].y, t[1].y};
        }
        else
        {
            double d[3];
            int u = 0;
            for (int j = 0; j < 3; j ++ )
            {
                auto o = get_line_intersection(t[j], t[(j + 1) % 3] - t[j], {a, -INF}, {0, INF * 2});
                if (dcmp(o.x, INF))
                    d[u ++ ] = o.y;
            }
            if (u)
            {
                sort(d, d + u);
                q[cnt ++ ] = {d[0], d[u - 1]};
            }
        }
    }
    if (!cnt) return 0;
    for (int i = 0; i < cnt; i ++ )
        if (q[i].x > q[i].y)
            swap(q[i].x, q[i].y);
        sort(q, q + cnt);
        double res = 0, st = q[0].x, ed = q[0].y;
        for (int i = 1; i < cnt; i ++ )
            if (q[i].x <= ed) ed = max(ed, q[i].y);
            else
            {
                res += ed - st;
                st = q[i].x, ed = q[i].y;
            }
            res += ed - st;
            return res;
}

double range_area(double a, double b)
{
    return (line_area(a, 1) + line_area(b, 0)) * (b - a) / 2;
}

int main()
{
    scanf("%d", &n);
    vector<double> xs;
    for (int i = 0; i < n; i ++ )
    {
        for (int j = 0; j < 3; j ++ )
        {
            scanf("%lf%lf", &tr[i][j].x, &tr[i][j].y);
            xs.push_back(tr[i][j].x);
        }
        sort(tr[i], tr[i] + 3);
    }
    for (int i = 0; i < n; i ++ )
        for (int j = i + 1; j < n; j ++ )
            for (int x = 0; x < 3; x ++ )
                for (int y = 0; y < 3; y ++ )
                {
                    auto o = get_line_intersection(tr[i][x], tr[i][(x + 1) % 3] - tr[i][x],
                                                   tr[j][y], tr[j][(y + 1) % 3] - tr[j][y]);
                    if (dcmp(o.x, INF))
                        xs.push_back(o.x);
                }
    sort(xs.begin(), xs.end());
                double res = 0;
                for (int i = 0; i + 1 < xs.size(); i ++ )
                    if (dcmp(xs[i], xs[i + 1]))
                        res += range_area(xs[i], xs[i + 1]);
                    printf("%.2lf\n", res);
                    return 0;
}