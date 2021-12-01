/*
 * 求sinx/x 从a到b的积分
 *
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps = 1e-12;

double f(double x)
{
    return sin(x) / x;
}

double simpson(double l, double r)
{
    auto mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
}

double asr(double l, double r, double s)
{
    auto mid = (l + r) / 2;
    auto left = simpson(l, mid), right = simpson(mid, r);
    if (fabs(left + right - s) < eps) return left + right;
    return asr(l, mid, left) + asr(mid, r, right);
}

int main()
{
    double l, r;
    scanf("%lf%lf", &l, &r);
    printf("%lf\n", asr(l, r, simpson(l, r)));
    return 0;
}