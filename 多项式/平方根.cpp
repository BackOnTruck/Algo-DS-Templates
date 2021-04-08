#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,g=3;
inline long long sqr(int a){return 1ll*a*a%mod;}
int pow(int a,int n)
{
	if(!n)return 1;
	if(n&1)return sqr(pow(a,n/2))*a%mod;
	return sqr(pow(a,n/2));
}
inline int inv(int a){return pow(a,mod-2);}
struct Int
{
	int r;
	Int(int x=0):r(x){}
	Int operator+(Int x){return (r+x.r)%mod;}
	Int operator-(Int x){return (r-x.r+mod)%mod;}
	Int operator*(Int x){return 1ll*r*x.r%mod;}
	Int &operator*=(Int x){return *this=*this*x;}
	void input(){scanf("%d",&r);r%=mod;}
};
int rev[300001],gpow[300001],ginv[300001];
template<int f>void ntt(Int *c,int n)
{
	for(int i=0;i<n;i++)
		if(rev[i]>i)swap(c[i],c[rev[i]]);
	for(int h=2;h<=n;h<<=1)
		for(int j=0;j<n;j+=h)
		{
			Int w=1,u=gpow[h];
			if(f==-1)u=ginv[h];
			for(int k=j;k<j+h/2;k++)
			{
				Int x=c[k],y=c[k+h/2];
				c[k]=x+w*y;
				c[k+h/2]=x-w*y;
				w*=u;
			}
		}
	if(f==-1)
	{
		int mul=inv(n);
		for(int i=0;i<n;i++)c[i]*=mul;
	}
}
Int a[300001],b[300001],c[300001],d[300001],f[300001];
inline void mul(int p,int q)
{
	int n=1,k=-1;
	while(n<=p+q)n<<=1,k++;
	for(int i=p;i<n;i++)a[i]=0;
	for(int i=q;i<n;i++)b[i]=0;
	for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
	ntt<1>(a,n);
	ntt<1>(b,n);
	for(int i=0;i<n;i++)a[i]*=b[i];
	ntt<-1>(a,n);
	ntt<-1>(b,n);
}
void inverse(int n)
{
	if(n==1)
	{
		b[0]=inv(c[0].r);
		return;
	}
	inverse((n+1)/2);
	for(int i=0;i<n;i++)a[i]=mod-c[i].r;
	mul(n,(n+1)/2);
	a[0]=a[0]+2;
	mul(n,(n+1)/2);
	for(int i=0;i<n;i++)swap(a[i],b[i]);
}
void logarithm(int n) // input: c, output: a
{
	inverse(n);
	for(int i=0;i<n;i++)a[i]=c[i+1]*(i+1);
	mul(n,n);
	for(int i=n-1;i>=0;i--)a[i]=(i?a[i-1]*inv(i):0);
}
void exponent(int n) // input: f, output: d
{
	if(n==1){d[0]=1;return;}
	int hn=(n+1)/2;
	exponent(hn);
	for(int i=0;i<hn;i++)c[i]=d[i];
	for(int i=hn;i<n;i++)c[i]=0;
	logarithm(n);
	for(int i=0;i<n;i++)a[i]=f[i]-a[i];
	a[0]=a[0]+1;
	for(int i=0;i<n;i++)b[i]=d[i];
	mul(n,n);
	for(int i=0;i<n;i++)d[i]=a[i];
}
int main()
{
	for(int i=2;i<=262144;i<<=1)ginv[i]=inv(gpow[i]=pow(g,(mod-1)/i));
	int n,k=499122177;
	scanf("%d",&n);
	for(int i=0;i<n;i++)c[i].input();
	logarithm(n);
	for(int i=0;i<n;i++)f[i]=a[i]*k;
	exponent(n);
	for(int i=0;i<n;i++)printf("%d ",d[i].r);
	puts("");
}
