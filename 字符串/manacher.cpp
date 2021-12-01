#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 100010;
char ma[maxn << 1],s[maxn];
int mp[maxn << 1];
void Manacher(char s[],int len)
{
    int l = 0;
    ma[l++] = '$';
    ma[l++] = '#';
    for(int i = 0;i < len; i++)
    {
        ma[l++] = s[i];
        ma[l++] = '#';
    }
    ma[l] = 0;
    /*i代表此刻字符串的位置
     * id代表此时最大回文子串的中心
     * mx代表当前得到的最大回文子串的右边界*/
    int mx = 0;
    int id = 0;
    for(int i = 0;i < l; i++)
    {
        mp[i] = mx > i ? min(mp[id * 2 - i],mx - i) : 1;
        while(ma[i + mp[i]] == ma[i - mp[i]])
            mp[i]++;
        if(i + mp[i] > mx)
        {
            mx = i + mp[i];
            id = i;
        }
    }
}
int main()
{
    while(scanf("%s",s) == 1)
    {
        int len = strlen(s);
        Manacher(s,len);
        int ans = 0;
        for(int i = 0;i < 2 * len + 2; i++)
            ans = max(ans,mp[i] - 1);
        printf("%d\n",ans);
    }
}

/*
* a b a a b a
* i:     0 1 2 3 4 5 6 7 8 9 10 11 12 13
* Ma[i]: $ # a # b # a # a # b  #  a  #
* Mp[i]: 1 1 2 1 4 1 2 7 2 1 4  1  2  1
*/