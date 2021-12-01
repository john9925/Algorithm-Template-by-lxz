#include<bits/stdc++.h>
using namespace std;
#define pb push_back
vector<int>A;
vector<int> div(vector<int>a,int b,int &r)
{
    vector<int>c;
    r=0;
    for(int i=a.size()-1;i>=0;i--)//从高位开始算
    {
        r=r*10+a[i];
        c.pb(r/b);
        r%=b;
    }
    reverse(c.begin(),c.end());
    while(c.size()>1&&c.back()==0)c.pop_back();
    return c;
}
int main()
{
    string a;
    int b;
    cin>>a>>b;
    for(int i=a.size()-1;i>=0;i--)A.pb(a[i]-'0');
    int r;
    auto c=div(A,b,r);
    for(int i=c.size()-1;i>=0;i--)cout<<c[i];
    cout<<endl;
    cout<<r;
    return 0;
}
