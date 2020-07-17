#include<bits/stdc++.h>
using namespace std;
constexpr const int mods[]={998244353,469762049,167772161},g=3;
template<int mod>inline long long sqr(int a){return 1ll*a*a%mod;}
template<int mod>int pow(int a,int n)
{
	if(!n)return 1;
	if(n&1)return sqr<mod>(pow<mod>(a,n/2))*a%mod;
	return sqr<mod>(pow<mod>(a,n/2));
}
template<int mod>inline int inv(int a){return pow<mod>(a,mod-2);}
template<int mod>struct Int
{
	int r;
	Int(int x=0):r(x){}
	Int operator+(Int x){return (r+x.r)%mod;}
	Int operator-(Int x){return (r-x.r+mod)%mod;}
	Int operator*(Int x){return 1ll*r*x.r%mod;}
	Int &operator*=(Int x){return *this=*this*x;}
	void input(){scanf("%d",&r);}
};
int rev[300001],gpow[3][300001],ginv[3][300001];
template<int mod>inline int Gpow(int x){return mod==mods[0]?gpow[0][x]:(mod==mods[1]?gpow[1][x]:gpow[2][x]);}
template<int mod>inline int Ginv(int x){return mod==mods[0]?ginv[0][x]:(mod==mods[1]?ginv[1][x]:ginv[2][x]);}
template<int mod>void ntt(Int<mod> *c,int n,int f)
{
	for(int i=0;i<n;i++)
		if(rev[i]>i)swap(c[i],c[rev[i]]);
	for(int h=2;h<=n;h<<=1)
		for(int j=0;j<n;j+=h)
		{
			Int<mod> w=1,u=Gpow<mod>(h);
			if(f==-1)u=Ginv<mod>(h);
			for(int k=j;k<j+h/2;k++)
			{
				Int<mod> x=c[k],y=c[k+h/2];
				c[k]=x+w*y;
				c[k+h/2]=x-w*y;
				w*=u;
			}
		}
	if(f==-1)
	{
		int mul=inv<mod>(n);
		for(int i=0;i<n;i++)c[i]*=mul;
	}
}
template<int mod>void exec(Int<mod> *a,Int<mod> *b,int n)
{
	ntt(a,n,1);
	ntt(b,n,1);
	for(int i=0;i<n;i++)a[i]*=b[i];
	ntt(a,n,-1);
}
int p,q,n=1,k=-1,mod;
Int<mods[0]> a[300001],b[300001];
Int<mods[1]> c[300001],d[300001];
Int<mods[2]> e[300001],f[300001];
int main()
{
	for(int i=2;i<=262144;i<<=1)
	{
		ginv[0][i]=inv<mods[0]>(gpow[0][i]=pow<mods[0]>(g,(mods[0]-1)/i));
		ginv[1][i]=inv<mods[1]>(gpow[1][i]=pow<mods[1]>(g,(mods[1]-1)/i));
		ginv[2][i]=inv<mods[2]>(gpow[2][i]=pow<mods[2]>(g,(mods[2]-1)/i));
	}
	scanf("%d%d%d",&p,&q,&mod);p++;q++;
	for(int i=0;i<p;i++)a[i].input(),c[i].r=e[i].r=a[i].r;
	for(int i=0;i<q;i++)b[i].input(),d[i].r=f[i].r=b[i].r;
	while(n<=p+q)n<<=1,k++;
	for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
	exec(a,b,n);
	exec(c,d,n);
	exec(e,f,n);
	__int128 m0=1ll*mods[1]*mods[2],m1=1ll*mods[0]*mods[2],m2=1ll*mods[0]*mods[1];
	for(int i=0;i<p+q-1;i++)printf("%d ",int((a[i].r*m0*inv<mods[0]>(m0%mods[0])+c[i].r*m1*inv<mods[1]>(m1%mods[1])+e[i].r*m2*inv<mods[2]>(m2%mods[2]))%(m0*mods[0])%mod));
	puts("");
	return 0;
}
