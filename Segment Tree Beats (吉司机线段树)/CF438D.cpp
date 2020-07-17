#include<bits/stdc++.h>
using namespace std;
struct tree
{
	int minv[1100001],maxv[1100001],setv[1100001];
	long long sumv[1100001];
	void build(int *a,int o,int l,int r)
	{
		setv[o]=-1;
		if(l==r){sumv[o]=minv[o]=maxv[o]=a[l];return;}
		int m=(l+r)/2;
		build(a,o*2,l,m);
		build(a,o*2+1,m+1,r);
		maintain(o);
	}
	void maintain(int o){maxv[o]=max(maxv[o*2],maxv[o*2+1]);minv[o]=min(minv[o*2],minv[o*2+1]);sumv[o]=sumv[o*2]+sumv[o*2+1];}
	void pushdown(int o,int l,int r)
	{
		if(l==r||setv[o]==-1)return;
		int m=(l+r)/2;
		setv[o*2]=setv[o*2+1]=minv[o*2]=maxv[o*2]=minv[o*2+1]=maxv[o*2+1]=setv[o];
		sumv[o*2]=1ll*setv[o]*(m-l+1);
		sumv[o*2+1]=1ll*setv[o]*(r-m);
		setv[o]=-1;
	}
	void mod(int x,int y,int d,int o,int l,int r)
	{
		if(maxv[o]<d)return;
		if(x<=l&&r<=y&&maxv[o]==minv[o])
		{
			setv[o]=minv[o]=maxv[o]%=d;
			sumv[o]=1ll*minv[o]*(r-l+1);
			return;
		}
		pushdown(o,l,r);
		int m=(l+r)/2;
		if(x<=m)mod(x,y,d,o*2,l,m);
		if(y>m)mod(x,y,d,o*2+1,m+1,r);
		maintain(o);
	}
	void set(int x,int d,int o,int l,int r)
	{
		if(l==r){sumv[o]=minv[o]=maxv[o]=d;return;}
		pushdown(o,l,r);
		int m=(l+r)/2;
		if(x<=m)set(x,d,o*2,l,m);
		else set(x,d,o*2+1,m+1,r);
		maintain(o);
	}
	long long query(int x,int y,int o,int l,int r)
	{
		if(x<=l&&r<=y)return sumv[o];
		pushdown(o,l,r);
		int m=(l+r)/2;
		long long ans=0;
		if(x<=m)ans+=query(x,y,o*2,l,m);
		if(y>m)ans+=query(x,y,o*2+1,m+1,r);
		return ans;
	}
}T;
int n,m,a[110001];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	T.build(a,1,1,n);
	while(m--)
	{
		int op,l,r,x;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1)printf("%lld\n",T.query(l,r,1,1,n));
		else if(op==2)scanf("%d",&x),T.mod(l,r,x,1,1,n);
		else T.set(l,r,1,1,n);
	}
}
