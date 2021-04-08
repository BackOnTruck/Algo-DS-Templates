#include<bits/stdc++.h>
using namespace std;
int p;
long long fac[100001],invf[100001];
inline long long sqr(int x){return 1ll*x*x%p;}
int pow(int a,int n)
{
	if(!n)return 1;
	if(n&1)return sqr(pow(a,n/2))*a%p;
	return sqr(pow(a,n/2));
}
inline int inv(int a){return pow(a,p-2);}
long long C(int n,int m)
{
	if(!m||n==m)return 1;
	if(n<m)return 0;
	if(n<p&&m<p)return fac[n]*invf[m]%p*invf[n-m]%p;
	return C(n/p,m/p)*C(n%p,m%p)%p;
}
int main()
{
	int t,n,m;
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>p;
		fac[1]=1;
		for(int i=2;i<p;i++)fac[i]=i*fac[i-1]%p;
		invf[p-1]=inv(fac[p-1]);
		for(int i=p-2;i;i--)invf[i]=(i+1)*invf[i+1]%p;
		cout<<C(n+m,m)<<endl;
	}
	return 0;
}
