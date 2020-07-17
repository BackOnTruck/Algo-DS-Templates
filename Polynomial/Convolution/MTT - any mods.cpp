#include<bits/stdc++.h>
#define float long double
using namespace std;
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
inline long long mul(const comp C,int mul,int mod){return (long long)(C.r+.5)%mod*mul%mod;}
int p,q,mod,n=1,k=-1,x;
comp a[300001],b[300001],c[300001],d[300001],H[300001],M[300001],L[300001];
int main()
{
	scanf("%d%d%d",&p,&q,&mod);p++;q++;
	for(int i=0;i<p;i++)scanf("%d",&x),a[i]=x/32768,b[i]=x%32768;
	for(int i=0;i<q;i++)scanf("%d",&x),c[i]=x/32768,d[i]=x%32768;
	while(n<=p+q)n<<=1,k++;
	for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
	fft(a,n,1);
	fft(b,n,1);
	fft(c,n,1);
	fft(d,n,1);
	for(int i=0;i<n;i++)H[i]=a[i]*c[i],M[i]=a[i]*d[i]+b[i]*c[i],L[i]=b[i]*d[i];
	fft(H,n,-1);
	fft(M,n,-1);
	fft(L,n,-1);
	for(int i=0;i<p+q-1;i++)printf("%lld ",(mul(H[i],1<<30,mod)+mul(M[i],1<<15,mod)+mul(L[i],1,mod))%mod);
	putchar('\n');
	return 0;
}
