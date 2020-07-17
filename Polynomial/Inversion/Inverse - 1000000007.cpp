#include<bits/stdc++.h>
#define float long double
using namespace std;
const int mod=1e9+7;
inline long long sqr(int a){return 1ll*a*a%mod;}
int pow(int a,int n)
{
	if(!n)return 1;
	if(n&1)return sqr(pow(a,n/2))*a%mod;
	return sqr(pow(a,n/2));
}
inline int inv(int a){return pow(a,mod-2);}
struct comp
{
	float r,i;
	comp(float a=0,float b=0):r(a),i(b){}
	comp operator+(comp x){return {r+x.r,i+x.i};}
	comp operator-(comp x){return {r-x.r,i-x.i};}
	comp operator*(comp x){return {r*x.r-i*x.i,r*x.i+i*x.r};}
	comp operator/(float x){return {r/x,i/x};}
	comp &operator*=(comp x){return *this=*this*x;}
	comp &operator/=(float x){return *this=*this/x;}
};
int rev[300001];
const float pi=acos(-1);
void fft(comp *c,int n,int f)
{
	for(int i=0;i<n;i++)
		if(rev[i]>i)swap(c[i],c[rev[i]]);
	for(int h=2;h<=n;h<<=1)
		for(int j=0;j<n;j+=h)
		{
			comp w=1,u(cos(pi*2/h),f*sin(pi*2/h));
			for(int k=j;k<j+h/2;k++)
			{
				comp x=c[k],y=c[k+h/2];
				c[k]=x+w*y;
				c[k+h/2]=x-w*y;
				w*=u;
			}
		}
	if(f==-1)for(int i=0;i<n;i++)c[i]/=n;
}
inline long long mul(const comp C,int x){return (long long)(C.r+.5)%mod*x%mod;}
namespace C_Array{comp a[300001],b[300001],c[300001],d[300001],H[300001],M[300001],L[300001];}
inline void mul(int *x,int *y,int *z,int p,int q)
{
	using namespace C_Array;
	for(int i=0;i<p;i++)a[i]=x[i]/32768,b[i]=x[i]%32768;
	for(int i=0;i<q;i++)c[i]=y[i]/32768,d[i]=y[i]%32768;
	int n=1,k=-1;
	while(n<=p+q)n<<=1,k++;
	for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
	for(int i=p;i<n;i++)a[i]=b[i]=0;
	for(int i=q;i<n;i++)c[i]=d[i]=0;
	fft(a,n,1);
	fft(b,n,1);
	fft(c,n,1);
	fft(d,n,1);
	for(int i=0;i<n;i++)H[i]=a[i]*c[i],M[i]=a[i]*d[i]+b[i]*c[i],L[i]=b[i]*d[i];
	fft(H,n,-1);
	fft(M,n,-1);
	fft(L,n,-1);
	for(int i=0;i<p+q-1;i++)z[i]=(mul(H[i],1<<30)+mul(M[i],1<<15)+mul(L[i],1))%mod;
}
int a[300001],b[300001],c[300001];
void proc(int n)
{
	if(n==1){b[0]=inv(c[0]);return;}
	proc((n+1)/2);
	for(int i=0;i<n;i++)a[i]=mod-c[i];
	mul(a,b,a,n,(n+1)/2);
	a[0]=(a[0]+2)%mod;
	mul(a,b,a,n,(n+1)/2);
	for(int i=0;i<n;i++)swap(a[i],b[i]);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d",c+i);
	proc(n);
	for(int i=0;i<n;i++)printf("%d ",b[i]);
	puts("");
}
