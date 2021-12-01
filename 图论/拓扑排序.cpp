#include<bits/stdc++.h>
using namespace std;
const int N=105;
vector<int>g[N];
int in[N],n;
void topos()
{
    int q[N],hh=0,tt=-1;
    for(int i=1;i<=n;i++)
        if(!in[i])q[++tt]=i;
        while(hh<=tt)
        {
            int t=q[hh++];
            for(auto i:g[t])
            {
                in[i]--;
                if(!in[i])
                    q[++tt]=i;
            }
        }
        for(int i=0;i<hh;i++)printf("%d ",q[i]);
}
int main()
{

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x;
        while(cin>>x,x)
        {
            g[i].push_back(x);
            in[x]++;
        }
    }
    topos();

    return 0;
}