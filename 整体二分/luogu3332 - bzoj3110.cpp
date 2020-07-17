#include<bits/stdc++.h>
using namespace std;
int n,k,qtot=0;
long long ans[110001];
struct tree
{
	long long sumv[660001],addv[660001];
	void pushdown(int o,int l,int r)
	{
		if(l==r||!addv[o])return;
		int m=(l+r)/2;
		add(addv[o],o*2,l,m);
		add(addv[o],o*2+1,m+1,r);
		addv[o]=0;
	}
	void add(long long d,int o,int l,int r){addv[o]+=d;sumv[o]+=d*(r-l+1);}
	void add(int x,int y,long long d,int o,int l,int r)
	{
		if(x<=l&&r<=y)return add(d,o,l,r);
		pushdown(o,l,r);
		int m=(l+r)/2;
		if(x<=m)add(x,y,d,o*2,l,m);
		if(y>m)add(x,y,d,o*2+1,m+1,r);
		sumv[o]=sumv[o*2]+sumv[o*2+1];
	}
	long long query(int x,int y,int o,int l,int r)
	{
		if(x<=l&&r<=y)return sumv[o];
		pushdown(o,l,r);
		int m=(l+r)/2;
		long long sum=0;
		if(x<=m)sum+=query(x,y,o*2,l,m);
		if(y>m)sum+=query(x,y,o*2+1,m+1,r);
		return sum;
	}
}T;
struct query
{
	int l,r,op,id;
	long long k;
	query(){}
	query(int x,int y,long long z):l(x),r(y),op(1),k(z){}
	query(int x,int y,long long z,int w):l(x),r(y),op(2),id(w),k(z){}
}q[660001],q1[660001],q2[660001];
void solve(int l,int r,int L,int R)
{
	if(L>R)return;
	if(l==r)
	{
		for(int i=L;i<=R;i++)
			if(q[i].op==2)ans[q[i].id]=l;
		return;
	}
	int m=(l+r)/2,c1=0,c2=0;
	for(int i=L;i<=R;i++)
		if(q[i].op==1)
			if(q[i].k<=m)q1[++c1]=q[i];
			else q2[++c2]=q[i],T.add(q[i].l,q[i].r,1,1,1,n);
		else
		{
			long long x=T.query(q[i].l,q[i].r,1,1,n);
			if(q[i].k<=x)q2[++c2]=q[i];
			else q[i].k-=x,q1[++c1]=q[i];
		}
	for(int i=1;i<=c2;i++)
		if(q2[i].op==1)T.add(q2[i].l,q2[i].r,-1,1,1,n);
	int pos=L;
	for(int i=1;i<=c1;i++,pos++)q[pos]=q1[i];
	for(int i=1;i<=c2;i++,pos++)q[pos]=q2[i];
	solve(l,m,L,L+c1-1);
	solve(m+1,r,L+c1,R);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,x,y,op;i<=k;i++)
	{
		long long z;
		scanf("%d%d%d%lld",&op,&x,&y,&z);
		if(op==2)q[i]=query(x,y,z,++qtot);
		else q[i]=query(x,y,z);
	}
	solve(0,100000,1,k);
	for(int i=1;i<=qtot;i++)printf("%lld\n",ans[i]);
}
