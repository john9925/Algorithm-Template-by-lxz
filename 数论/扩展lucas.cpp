//多组询问，给出N,K,M，要求回答C(N,K)%M，1<=N<=10^18,1<=K<=N,2<=M<=10^6
using namespace std;
typedef long long LL;
const int maxn=1000005;

LL N,K; int M;
int pri[maxn],tot; bool ntp[maxn];

void get_pri(){
    ntp[0]=ntp[1]=1;
    for(int i=2;i<=1000000;i++){
        if(!ntp[i]) pri[++tot]=i;
        for(int j=1;j<=tot&&1ll*pri[j]*i<=1000000;j++){
            ntp[pri[j]*i]=1;
            if(i%pri[j]==0) break;
        }
    }
}
void exgcd(int a,int b,LL &d,LL &x,LL &y){
    if(!b) d=a,x=1,y=0;
    else exgcd(b,a%b,d,y,x),y-=a/b*x;
}
int inv(int a,int p){
    LL d,x,y; exgcd(a,p,d,x,y);
    return (x%p+p)%p;
}
int qkpow(int x,LL y,int p){
    int re=1,t=x;
    for(int i=0;(1ll<<i)<=y;i++){
        if((1ll<<i)&y) re=1ll*re*t%p;
        t=1ll*t*t%p;
    }
    return re;
}
int J(LL n,int p,int pt,int mul){
    if(n<=1) return 1;
    int re=1;
    if(n>=pt) re=qkpow(mul,n/pt,pt);
    for(int i=1;i<=n%pt;i++)
        if(i%p) re=1ll*re*i%pt;
        return 1ll*re*J(n/p,p,pt,mul)%pt;
}
int C(LL n,LL m,int p,int pt){
    LL k=0,t;
    for(t=n;t;t/=p) k+=t/p;
    for(t=m;t;t/=p) k-=t/p;
    for(t=n-m;t;t/=p) k-=t/p;
    int pw=qkpow(p,k,pt); if(!pw) return 0;
    int mul=1;
    for(int i=1;i<pt;i++)
        if(i%p) mul=1ll*mul*i%pt;
        int a=J(n,p,pt,mul),b=inv(J(m,p,pt,mul),pt),c=inv(J(n-m,p,pt,mul),pt);
        return 1ll*pw*a%pt*b%pt*c%pt;
}
int exLucas(LL n,LL m,int p){
    int re=0,t=p;
    for(int i=1;i<=tot&&pri[i]<=t;i++){
        if(t%pri[i]) continue;
        int pt=1,c;
        while(t%pri[i]==0) pt*=pri[i],t/=pri[i];
        c=C(n,m,pri[i],pt);
        re=(re+1ll*p/pt*c%p*inv(p/pt,pt)%p)%p;
    }
    return re;
}
int main()
{
    get_pri();
    while(cin>>N>>K>>M) cout<<exLucas(N,K,M)<<'\n';
    return 0;
}