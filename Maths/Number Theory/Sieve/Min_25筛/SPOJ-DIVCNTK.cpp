#include<bits/stdc++.h>
using namespace std;
using lint=unsigned long long;
const int lim=1e6;
int p[lim+10],T,Pcnt,pcnt,m,id1[lim+10],id2[lim+10];
lint n,q,w[lim+10],g[lim+10],root;
bool f[lim+10];
lint S(lint x,int y)
{
	if(x<2||p[y]>x)return 0;
	int k=(x<=root?id1[x]:id2[n/x]);
	lint ans=(g[k]-y+1)*(q+1);
	for(int i=y;i<=pcnt&&1ll*p[i]*p[i]<=x;i++)
	{
		lint p1=p[i],p2=p1*p1;
		for(int e=1;p2<=x;e++,p1=p2,p2*=p[i])ans+=(e+1)*q+1+(e*q+1)*S(x/p1,i+1);
	}
	return ans;
}
int main()
{
	f[1]=1;
	for(int i=2;i<=lim;i++)
		if(!f[i])
		{
			p[++Pcnt]=i;
			for(int j=2*i;j<=lim;j+=i)f[j]=1;
		}
	scanf("%d",&T);
	while(T--)
	{
		scanf("%llu%llu",&n,&q);
		m=0;
		root=sqrt(n);
		pcnt=upper_bound(p+1,p+Pcnt+1,root)-p-1;
		for(lint i=1,j;i<=n;i=j+1)
		{
			j=n/(n/i);
			w[++m]=n/i;
			if(w[m]<=root)id1[w[m]]=m;
			else id2[n/w[m]]=m;
			g[m]=w[m]-1;
		}
		for(int j=1;j<=pcnt;j++)
			for(int i=1;i<=m&&1ll*p[j]*p[j]<=w[i];i++)
			{
				int k=(w[i]/p[j]<=root?id1[w[i]/p[j]]:id2[n/(w[i]/p[j])]);
				g[i]-=g[k]-j+1;
			}
		printf("%llu\n",S(n,1)+1);
	}
}
