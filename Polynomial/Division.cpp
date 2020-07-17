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
Int a[300001],b[300001],c[300001],d[300001];
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
void proc(int n)
{
	if(n==1)
	{
		b[0]=inv(c[0].r);
		return;
	}
	proc((n+1)/2);
	for(int i=0;i<n;i++)a[i]=mod-c[i].r;
	mul(n,(n+1)/2);
	a[0]=a[0]+2;
	mul(n,(n+1)/2);
	for(int i=0;i<n;i++)swap(a[i],b[i]);
}
int n,m;
int main()
{
	for(int i=2;i<=262144;i<<=1)ginv[i]=inv(gpow[i]=pow(g,(mod-1)/i));
	scanf("%d%d",&n,&m);n++;m++;
	for(int i=0;i<n;i++)d[n-i-1].input();
	for(int i=0;i<m;i++)c[m-i-1].input();
	const int len=n-m+1;
	proc(len);
	memset(a,0,sizeof a);
	for(int i=0;i<len;i++)a[i]=d[i];
	mul(len,len);
	reverse(a,a+len);
	for(int i=0;i<len;i++)printf("%d ",a[i].r);
	puts("");
	for(int i=len;i<300000;i++)a[i]=0;
	memset(b,0,sizeof b);
	for(int i=0;i<m;i++)b[i]=c[m-i-1];
	mul(len,m);
	reverse(d,d+n);
	for(int i=0;i<m-1;i++)printf("%d ",(d[i]-a[i]).r);
	puts("");
}
