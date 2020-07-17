#include<bits/stdc++.h>
#define int long long
#define pow fuck
using namespace std;
const int mod=1e9+7;
int sqr(int x){return x*x%mod;}
int pow(int a,int n){return !n?1:sqr(pow(a,n/2))*(n&1?a:1)%mod;}
int n,a[501][901];
main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)scanf("%lld",a[i]+j);
		a[i][n+i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
			if(a[j][i])
			{
				for(int k=1;k<=2*n;k++)swap(a[j][k],a[i][k]);
				break;
			}
		if(!a[i][i])puts("No Solution"),exit(0);
		int q=pow(a[i][i],mod-2);
		for(int j=i;j<=2*n;j++)a[i][j]=a[i][j]*q%mod;
		for(int j=1;j<=n;j++)
			if(i!=j)
			{
				q=a[j][i];
				for(int k=i;k<=2*n;k++)a[j][k]=(a[j][k]-q*a[i][k]%mod+mod)%mod;
			}
	}
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)printf("%lld ",a[i][j+n]);
}
