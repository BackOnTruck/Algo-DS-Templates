#include<bits/stdc++.h>
#define lim 2500000
using namespace std;
long long rec[10001];
bool vis[10001];
int t,m;
template<long long *f,bool init>long long calc(int x)
{
	int n=m/x;
	if(n<=lim)return f[n];
	if(vis[x])return rec[x];
	vis[x]=1;
	long long ans=init?1:n*(n+1ll)/2;
	int bound=n/((int)floor(sqrt(n)+.5)-1);
	for(int i=2;i<=bound;i++)ans-=calc<f,init>(x*i);
	for(int i=bound;i<n;)
	{
		int next_i=n/(n/i-1);
		ans-=(next_i-i)*calc<f,init>(x*next_i);
		i=next_i;
	}
	return rec[x]=ans;
}
bool f[lim+50];
long long mu[lim+50],phi[lim+50];
int p[lim],tot=0;
int main()
{
	mu[1]=phi[1]=1;
	for(int i=2;i<=lim;i++)
	{
		if(!f[i])p[tot++]=i,mu[i]=-1,phi[i]=i-1;
		for(int j=0;j<tot;j++)
		{
			long long x=1ll*i*p[j];
			if(x>lim)break;
			f[x]=1;
			if(i%p[j])mu[x]=-mu[i],phi[x]=phi[i]*phi[p[j]];
			else {mu[x]=0;phi[x]=phi[i]*p[j];break;}
		}
	}
	for(int i=2;i<=lim;i++)mu[i]+=mu[i-1],phi[i]+=phi[i-1];
	cin>>t;
	while(t--)
	{
		cin>>m;
		memset(vis,0,sizeof vis);
		cout<<calc<phi,0>(1)<<' ';
		memset(vis,0,sizeof vis);
		cout<<calc<mu,1>(1)<<endl;
	}
	return 0;
}
