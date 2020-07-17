#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct complex
{
	double r,i;
	complex(double a=0,double b=0):r(a),i(b){}
	complex operator+(complex x){return {r+x.r,i+x.i};}
	complex operator-(complex x){return {r-x.r,i-x.i};}
	complex operator*(complex x){return {r*x.r-i*x.i,r*x.i+i*x.r};}
	complex operator/(double x){return {r/x,i/x};}
	complex &operator*=(complex x){return *this=*this*x;}
	complex &operator/=(double x){return *this=*this/x;}
}a[300001],b[300001];
int rev[300001];
const double pi=acos(-1);
void fft(complex *c,int n,int f)
{
	for(int i=0;i<n;i++)
		if(rev[i]>i)swap(c[i],c[rev[i]]);
	for(int h=2;h<=n;h<<=1)
		for(int j=0;j<n;j+=h)
		{
			complex w=1,u(cos(pi*2/h),f*sin(pi*2/h));
			for(int k=j;k<j+h/2;k++)
			{
				complex x=c[k],y=c[k+h/2];
				c[k]=x+w*y;
				c[k+h/2]=x-w*y;
				w*=u;
			}
		}
	if(f==-1)for(int i=0;i<n;i++)c[i]/=n;
}
int p,q,n=1,k=-1,x;
int main()
{
	scanf("%d%d",&p,&q);p++;q++;
	for(int i=0;i<p;i++)scanf("%d",&x),a[i]=x;
	for(int i=0;i<q;i++)scanf("%d",&x),b[i]=x;
	while(n<=p+q)n<<=1,k++;
	for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
	fft(a,n,1);
	fft(b,n,1);
	for(int i=0;i<n;i++)a[i]*=b[i];
	fft(a,n,-1);
	for(int i=0;i<p+q-1;i++)printf("%d ",int(a[i].r+.5));
	putchar('\n');
	return 0;
}
