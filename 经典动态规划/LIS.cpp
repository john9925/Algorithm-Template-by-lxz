int a[N],q[N];
void solve()
{
    int n;
    n=read();
    for(int i=0;i<n;i++)a[i]=read(),q[i]=0;
    q[0]=-2e9;
    int len1=0;
    for(int i=0;i<n;i++)//非递减
        {
        int l=0,r=len1;
        while(l<r)
        {
            int mid=l+r+1>>1;
            if(q[mid]<=a[i])l=mid;
            else r=mid-1;

        }
        len1=max(len1,r+1);
        q[r+1]=a[i];
        }
    int len2=0;
    for(int i=0;i<n;i++)q[i]=0;
    q[0]=2e9;
    for(int i=0;i<n;i++)//非递增
        {
        int l=0,r=len2;
        while(l<r)
        {
            int mid=l+r+1>>1;
            if(q[mid]>=a[i])l=mid;
            else r=mid-1;

        }
        len2=max(len2,r+1);
        q[r+1]=a[i];
        }
    if(len1>=n-1||len2>=n-1)puts("YES");
    else puts("NO");
}
int main()
{

    int t;
    cin>>t;
    //t=1;
    for(int i=1;i<=t;i++)
    {
        //printf("Case #%d: ",i);
        solve();
    }
    return 0;
}

