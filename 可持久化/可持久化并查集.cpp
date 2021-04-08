#include<bits/stdc++.h>
using namespace std;
struct pstree
{
	int tot=0,val[5000001],lc[5000001],rc[5000001],root[250001];
	void build(int &o,int l,int r,bool f)
	{
		o=++tot;
		if(l==r){val[o]=(f?l:1);return;}
		int m=(l+r)/2;
		build(lc[o],l,m,f);
		build(rc[o],m+1,r,f);
	}
	int modify(int o,int l,int r,int p,int v)
	{
		int newv=++tot;
		lc[newv]=lc[o];
		rc[newv]=rc[o];
		if(l==r){val[newv]=v;return newv;}
		int m=(l+r)/2;
		if(p<=m)lc[newv]=modify(lc[newv],l,m,p,v);
		else rc[newv]=modify(rc[newv],m+1,r,p,v);
		return newv;
	}
	int query(int o,int l,int r,int p)
	{
		if(l==r)return val[o];
		int m=(l+r)/2;
		return p<=m?query(lc[o],l,m,p):query(rc[o],m+1,r,p);
	}
}f,d;
int n,m;
int find(int p,int v)
{
	int q=f.query(f.root[v],1,n,p);
	if(p==q)return p;
	return find(q,v);
}
int main()
{
	scanf("%d%d",&n,&m);
	f.build(f.root[0],1,n,1);
	d.build(d.root[0],1,n,0);
	for(int i=1;i<=m;i++)
	{
		int op,a,b;
		scanf("%d%d",&op,&a);
		if(op==2)f.root[i]=f.root[a],d.root[i]=d.root[a];
		else
		{
			scanf("%d",&b);
			if(op==1)
			{
				int d1=d.query(d.root[i-1],1,n,a),d2=d.query(d.root[i-1],1,n,b);
				if(d1<d2)swap(a,b),swap(d1,d2);
				int nd=max(d1,d2+1);
				d.root[i]=d.modify(d.modify(d.root[i-1],1,n,a,nd),1,n,b,nd);
				f.root[i]=f.modify(f.root[i-1],1,n,find(b,i-1),find(a,i-1));
			}
			else
			{
				f.root[i]=f.root[i-1];
				d.root[i]=d.root[i-1];
				int r1=find(a,i),r2=find(b,i);
				printf("%d\n",int(r1==r2));
			}
		}
	}
	return 0;
}
