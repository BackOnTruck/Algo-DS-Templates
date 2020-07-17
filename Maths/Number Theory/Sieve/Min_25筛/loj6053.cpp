#include<bits/stdc++.h>
using namespace std;
using lint=long long;
const int lim=1e6,mod=1e9+7,inv2=(mod+1)/2;
int p[lim+10],T,pcnt,m,id1[lim+10],id2[lim+10];
lint n,w[lim+10],g[lim+10],h[lim+10],s[lim+10],root;
bool f[lim+10];
lint S(lint x,int y)
{
	if(x<2||p[y]>x)return 0;
	int k=(x<=root?id1[x]:id2[n/x]);
	lint ans=(((g[k]-s[y-1])-(h[k]-y+1))%mod+mod)%mod;
	if(y==1)ans+=2;
	for(int i=y;i<=pcnt&&1ll*p[i]*p[i]<=x;i++)
	{
		lint p1=p[i],p2=p1*p1;
		for(int e=1;p2<=x;e++,p1=p2,p2*=p[i])ans=(ans+(p[i]^(e+1))+(p[i]^e)*S(x/p1,i+1))%mod;
	}
	return ans;
}
int main()
{
	scanf("%lld",&n);
	root=sqrt(n);
	f[1]=1;
	for(int i=2;i<=root;i++)
		if(!f[i])
		{
			p[++pcnt]=i;
			s[pcnt]=(s[pcnt-1]+i)%mod;
			for(int j=2*i;j<=root;j+=i)f[j]=1;
		}
	for(lint i=1,j;i<=n;i=j+1)
	{
		j=n/(n/i);
		w[++m]=n/i;
		if(w[m]<=root)id1[w[m]]=m;
		else id2[n/w[m]]=m;
		h[m]=(w[m]-1+mod)%mod;
		g[m]=(w[m]+2)%mod*h[m]%mod*inv2%mod;
	}
	for(int j=1;j<=pcnt;j++)
		for(int i=1;i<=m&&1ll*p[j]*p[j]<=w[i];i++)
		{
			int k=(w[i]/p[j]<=root?id1[w[i]/p[j]]:id2[n/(w[i]/p[j])]);
			g[i]=(g[i]-p[j]*(g[k]-s[j-1]+mod)%mod+mod)%mod;
			h[i]=(h[i]-h[k]+j-1+mod)%mod;
		}
	printf("%lld\n",S(n,1)+1);
}
