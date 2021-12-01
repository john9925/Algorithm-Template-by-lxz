/*
套路
题目给出Fn=。。。。
自己写出Fn+1=。。。。
然后有Fn * A = Fn+1
注意Fn和Fn+1写出矩阵的形式必须是对应的（n对应n-1等等）
然后根据Fn的行列和Fn+1的行列，就可以知道A的行列。
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 10;
const ll mod = 2147493647;

#define pid pair<int,double>
#define pii pair<int,int>

struct Mat {
    ll m[N][N];

    Mat()//记得写，不然超时
    {
        memset(m, 0, sizeof m);
    }

    void build() {
        for (int i = 0; i < N; i++)m[i][i] = 1;
    }
} a, ans, org;//a是常数矩阵，ans是快速幂中存答案用的，org是原矩阵（A左边那个）。
int n = 7;//矩阵的行列数
Mat operator*(Mat &a, Mat &b) {
    Mat tmp;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)tmp.m[i][j] = (tmp.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
    return tmp;
}

void qp(ll b) {
    ans = Mat();
    ans.build();
    while (b) {
        if (b & 1)ans = ans * a;
        b >>= 1;
        a = a * a;
    }
}

int x[N][N] = {     //构造的常数矩阵
        {0, 2, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 2, 1, 0, 0},
        {0, 1, 1, 3, 3, 1, 0},
        {0, 1, 1, 4, 6, 4, 1}

};

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n, A, B;
        scanf("%lld%lld%lld", &n, &A, &B);
        if (n == 1)printf("%lld\n", A);
        else if (n == 2)printf("%lld\n", B);
        else {
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)a.m[i + 1][j + 1] = x[i][j];
            qp(n - 2);
            org = Mat();
            org.m[1][1] = A, org.m[1][2] = B, org.m[1][3] = 2 * 2 * 2 * 2, org.m[1][4] = 4 * 2 * 2 * 2, org.m[1][5] =
                    6 * 2 * 2, org.m[1][6] = 4 * 2, org.m[1][7] = 1;
            org = org * ans;
            printf("%lld\n", org.m[1][2]);
        }

    }

    return 0;
}
