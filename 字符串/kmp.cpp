//2020/7/27
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
char p[N],s[N];
int ne[N];
int main()
{
    int lp,ls;
    scanf("%d%s",&lp,p+1);
    scanf("%d%s",&ls,s+1);
    for(int i=1,j=0;i<=lp;)//不需要i++
    {
        if(j==0||p[i]==p[j])ne[++i]=++j;
        else j=ne[j];
    }
    int i=1,j=1;
    while(i<=ls)
    {
        if(p[j]==s[i]||j==0)
        {
            i++;
            j++;
            if(j>lp)
            {
                cout<<i-j<<' ';
                j=ne[j];
            }
        }
        else j=ne[j];
    }

    return 0;
}