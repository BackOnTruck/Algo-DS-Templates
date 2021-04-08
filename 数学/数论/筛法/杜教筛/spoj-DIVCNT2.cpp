#include<bits/stdc++.h>
#define maxn 110000000
using namespace std;
short mu[maxn+5],pcnt[maxn+5];
int p[maxn/10],tot,lim=maxn,f[maxn+5];
long long g[maxn+5];
bool flag[maxn+5];
long long F(long long n)
{
	if(n<=lim)return f[n];
	int bound=(int)floor(sqrt(n)+.5);
	long long ans=0;
	for(int i=1;i<=bound;i++)ans+=mu[i]*(n/(1ll*i*i));
	return ans;
}
long long G(long long n)
{
	if(n<=lim)return g[n];
	long long ans=0;
	int bound=int(n/max(1,(int)floor(sqrt(n)+.5)-1));
	for(int i=1;i<=bound;i++)ans+=n/i;
	for(long long i=bound;i<n;)
	{
		long long next_i=n/(n/i-1);
		ans+=(next_i-i)*(n/next_i);
		i=next_i;
	}
	return ans;
}
int T;
long long q[20001],top;
int main()
{
	scanf("%d",&T);
	for(int i=0;i<T;i++)scanf("%lld",q+i),top=max(top,q[i]);
	lim=(int)min(1ll*lim,top);
	g[1]=mu[1]=1;
	for(int i=2;i<=lim;i++)
	{
		if(!flag[i])p[tot++]=i,mu[i]=-1,g[i]=2,pcnt[i]=1;
		for(int j=0;j<tot;j++)
		{
			long long x=1ll*i*p[j];
			if(x>lim)break;
			flag[x]=1;
			if(i%p[j])mu[x]=-mu[i],pcnt[x]=1,g[x]=g[i]*2;
			else{mu[x]=0;pcnt[x]=pcnt[i]+1;g[x]=g[i]/pcnt[x]*(pcnt[x]+1);break;}
		}
	}
	for(int i=1;i<=lim;i++)f[i]=f[i-1]+mu[i]*mu[i],g[i]+=g[i-1];
	for(int l=0;l<T;l++)
	{
		long long n=q[l],ans=0;
		int bound=int(n/max(1,(int)floor(sqrt(n)+.5)-1));
		for(int i=1;i<=bound;i++)ans+=mu[i]*mu[i]*G(n/i);
		for(long long i=bound,pre=F(i);i<n;)
		{
			long long next_i=n/(n/i-1),cur=F(next_i);
			ans+=G(n/next_i)*(cur-pre);
			i=next_i;pre=cur;
		}
		printf("%lld\n",ans);
	}
}
