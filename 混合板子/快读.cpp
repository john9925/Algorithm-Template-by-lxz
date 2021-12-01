//普通快读
inline ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
//高速快读，本地无法使用，在oj上才可以。会增加空间开销
inline char nc() {
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename _Tp> inline void read(_Tp&sum) {
    char ch = nc(); sum = 0;
    while (!(ch >= '0'&&ch <= '9')) ch = nc();
    while (ch >= '0'&&ch <= '9') sum = (sum << 3) + (sum << 1) + (ch - 48), ch = nc();
}
