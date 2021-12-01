int lowbit(int x)
{
    return x&-x;
}
int ask(int x)//x前缀和
{
    int res=0;
    for(int i=x;i;i-=lowbit(i))res+=tr[i];
    return res;
}
void add(int x,int c)
{
    for(int i=x;i<=n;i+=lowbit(i))tr[i]+=c;
}