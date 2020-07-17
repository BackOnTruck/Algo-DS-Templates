#include<bits/stdc++.h>
using namespace std;
const int mods[]={1004535809,998244353,469762049,167772161,104857601,23068673,7340033,5767169};
int n,m,a[31],sum[31],id[31];
double ave,ans=1e300;
inline double sqr(double x){return x*x;}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",a+i),ave+=a[i];
	ave/=m;
	for(int i=0;i<20000;i++)
	{
		if(i%2500==0)srand(mods[i/2500]);
		memset(sum,0,sizeof sum);
		for(int j=0;j<n;j++)sum[id[j]=rand()%m]+=a[j];
		double cur=0;
		for(int j=0;j<m;j++)cur+=sqr(sum[j]-ave);
		double T=15000000;
		while(T>.1)
		{
			T*=.9;
			int t=rand()%n,x=id[t],y=(T>5000?min_element(sum,sum+m)-sum:rand()%m);
			if(x==y)continue;
			double old=cur;
			cur-=sqr(sum[x]-ave)+sqr(sum[y]-ave);
			sum[x]-=a[t];sum[y]+=a[t];
			cur+=sqr(sum[x]-ave)+sqr(sum[y]-ave);
			if(cur<old||(1ll*rand()*rand()+rand())%15000000<T)id[t]=y;
			else sum[x]+=a[t],sum[y]-=a[t],cur=old;
		}
		ans=min(ans,cur);
	}
	printf("%.2f\n",sqrt(ans/m));
	return 0;
}
