#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int sqr(int x){return x*x%mod;}
int pow(int a,int n){return !n?1:sqr(pow(a,n/2))*(n&1?a:1)%mod;}
int inv(int x){return pow(x,mod-2);}
int n,q,x[5001],y[5001];
main()
{
	cin>>n>>q;
	for(int i=0;i<n;i++)cin>>x[i]>>y[i];
	int ans=0;
	for(int j=0;j<n;j++)
	{
		int f=y[j],g=1;
		for(int k=0;k<n;k++)
			if(k!=j)f=f*(q-x[k]+mod)%mod,g=g*(x[j]-x[k]+mod)%mod;
		ans+=f*inv(g)%mod;
	}
	cout<<ans%mod<<'\n';
}
