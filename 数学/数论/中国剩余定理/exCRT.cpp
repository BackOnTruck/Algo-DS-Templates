#include<cstdio>
#define int long long
void gcd(int a,int b,int &d,int &x,int &y)
{
	if(!b){d=a;x=1;y=0;return;}
	gcd(b,a%b,d,y,x);
	y-=a/b*x;
}
int mul(int a,int n,int m)
{
	if(!n)return 1;
	return (2*mul(a,n/2,m)+(n&1?a:1))%m;
}
int n,a[110001],m[110001];
main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",m+i,a+i);
	int x=a[1],M=m[1];
	for(int i=2;i<=n;i++)
	{
		int d,p,q,ai=((a[i]-x)%m[i]+m[i])%m[i];
		gcd(M,m[i],d,p,q);
		p=mul((p%m[i]+m[i])%m[i],ai/d,m[i]);
		int newM=M/d*m[i];
		x=(x+mul(p,M,newM))%newM;
		printf("now x = %lld\n",x);
	}
	printf("%lld\n",x);
}
