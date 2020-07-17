#include<bits/stdc++.h>
using namespace std;
int c[660001],n,ans[220001],k,a[220001],tot=0,qtot=0;
void add(int x,int d){while(x<=n)c[x]+=d,x+=x&-x;}
int sum(int x)
{
	int res=0;
	while(x)res+=c[x],x-=x&-x;
	return res;
}
struct query
{
	int l,r,k,op,id,add;
	query(){}
	query(int x,int y,int ad):k(y),op(1),id(x),add(ad){}
	query(int x,int y,int z,int w):l(x),r(y),k(z),op(2),id(w){}
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
			if(q[i].k<=m)q1[++c1]=q[i],add(q[i].id,q[i].add);
			else q2[++c2]=q[i];
		else
		{
			int x=sum(q[i].r)-sum(q[i].l-1);
			if(q[i].k<=x)q1[++c1]=q[i];
			else q[i].k-=x,q2[++c2]=q[i];
		}
	for(int i=1;i<=c1;i++)
		if(q1[i].op==1)add(q1[i].id,-q1[i].add);
	int pos=L;
	for(int i=1;i<=c1;i++,pos++)q[pos]=q1[i];
	for(int i=1;i<=c2;i++,pos++)q[pos]=q2[i];
	solve(l,m,L,L+c1-1);
	solve(m+1,r,L+c1,R);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",a+i),q[++tot]=query(i,a[i],1);
	for(int i=1;i<=k;i++)
	{
		int x,y,z;
		char op[10];
		scanf("%s%d%d",op,&x,&y);
		if(op[0]=='Q')scanf("%d",&z),q[++tot]=query(x,y,z,++qtot);
		else q[++tot]=query(x,a[x],-1),q[++tot]=query(x,a[x]=y,1);
	}
	solve(0,1e9,1,tot);
	for(int i=1;i<=qtot;i++)printf("%d\n",ans[i]);
}
