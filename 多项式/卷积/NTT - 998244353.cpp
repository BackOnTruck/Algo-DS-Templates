#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,g=3;
inline int sqr(int a){return 1ll*a*a%mod;}
int pow(int a,int n)
{
	if(!n)return 1;
	if(n&1)return 1ll*sqr(pow(a,n/2))*a%mod;
	return sqr(pow(a,n/2));
}
inline int inv(int a){return pow(a,mod-2);}
struct Int
{
	int r;
	Int(int x=0):r(x%mod){}
	Int operator+(Int x){return (r+x.r)%mod;}
	Int operator-(Int x){return (r-x.r+mod)%mod;}
	Int operator*(Int x){return 1ll*r*x.r%mod;}
	Int &operator*=(Int x){return *this=*this*x;}
	void input(){scanf("%d",&r);r%=mod;}
}a[300001],b[300001];
int rev[300001],ginv[300001],gpow[300001];
void ntt(Int *c,int n,int f)
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
int p,q,n=1,k=-1,x;
int main()
{
	for(int i=2;i<524288;i<<=1)ginv[i]=inv(gpow[i]=pow(g,(mod-1)/i));
	scanf("%d%d",&p,&q);p++;q++;
	for(int i=0;i<p;i++)a[i].input();
	for(int i=0;i<q;i++)b[i].input();
	while(n<=p+q)n<<=1,k++;
	for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
	ntt(a,n,1);
	ntt(b,n,1);
	for(int i=0;i<n;i++)a[i]*=b[i];
	ntt(a,n,-1);
	for(int i=0;i<p+q-1;i++)printf("%d ",a[i].r);
	putchar('\n');
	return 0;
}
