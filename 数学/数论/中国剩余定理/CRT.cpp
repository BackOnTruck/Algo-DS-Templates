#include<iostream>
#define int long long
using namespace std;
void gcd(int a,int b,int &d,int &x,int &y)
{
	if(!b){d=a;x=1;y=0;return;}
	gcd(b,a%b,d,y,x);
	y-=a/b*x;
}
int inv(int a,int m)
{
	int d,x,y;
	gcd(a,m,d,x,y);
	return (x%m+m)%m;
}
int n,a[12],m[12];
main()
{
	cin>>n;
	int M=1,x=0;
	for(int i=1;i<=n;i++)cin>>m[i]>>a[i],M*=m[i];
	for(int i=1;i<=n;i++)
	{
		int mi=M/m[i];
		x=(x+mi*a[i]*inv(mi,m[i]))%M;
	}
	cout<<x<<endl;
}
