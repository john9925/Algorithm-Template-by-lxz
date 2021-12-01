//方程组中的系数和常数为 0 或 1，每个未知数的取值也为 0 或 1，等号右边也是0或1。
//多组输入切记清空a数组
//普通版本
//n行m列的高斯消元板子，此时m-r就是自由元的个数（自由元可以随意取值）
int n,m;//n行m列（m个未知数），如果等号右边要设置值的话则是m+1列，默认0.
int a[310][310];
int gauss()//返回矩阵的秩
{
    int c, r;
    for (c = 0, r = 0; c < n; c ++ )
    {
        int t = r;
        for (int i = r; i < n; i ++ )
            if (a[i][c])
                t = i;

            if (!a[t][c]) continue;

            for (int i = c; i <= m; i ++ ) swap(a[r][i], a[t][i]);
            for (int i = r + 1; i < n; i ++ )
                if (a[i][c])
                    for (int j = m; j >= c; j -- )
                        a[i][j] ^= a[r][j];

                    r ++ ;
    }
    return r;
}
//此时m-r就是自由元的个数（自由元可以随意取值）
//bitset优化版本，复杂度/64,下标从0开始
bitset<N>a[N];
ll gauss(int n,int m)
{
    int row = 0,col = 0,maxx;
    for(; col < m && row < n ;++ col){
        for(maxx = row ;maxx < n;++maxx){
            if(a[maxx][col])
                break;
        }
        if(a[maxx][col] == 0)
            continue;

        swap(a[maxx],a[row]);
        for(int i = row + 1;i < n; ++i){
            if(a[i][col])
                a[i] ^= a[row];
        }
        row++;
    }
    return m-row;//m-row就是自由元个数
}

//解出每个变量答案
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;


int n,m;
int a[N][N];


int gauss()
{
    int c, r;
    for (c = 0, r = 0; c < n; c ++ )
    {
        int t = r;
        for (int i = r; i < n; i ++ )
            if (a[i][c])
                t = i;

            if (!a[t][c]) continue;

            for (int i = c; i <= m; i ++ ) swap(a[r][i], a[t][i]);
            for (int i = r + 1; i < n; i ++ )
                if (a[i][c])
                    for (int j = m; j >= c; j -- )
                        a[i][j] ^= a[r][j];

                    r ++ ;
    }

    if (r < n)
    {
        for (int i = r; i < n; i ++ )
            if (a[i][n])
                return 2;
            return 1;
    }

    for (int i = n - 1; i >= 0; i -- )
        for (int j = i + 1; j < n; j ++ )
            a[i][n] ^= a[i][j] * a[j][n];

        return 0;
}


int main()
{
    cin >> n;
    m=n;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m + 1; j ++ )
            cin >> a[i][j];

        int t = gauss();

        if (t == 0)
        {
            for (int i = 0; i < n; i ++ ) cout << a[i][n] << endl;
        }
        else if (t == 1) puts("Multiple sets of solutions");
        else puts("No solution");

        return 0;
}
