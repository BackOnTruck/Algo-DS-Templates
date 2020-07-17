#include<bits/stdc++.h>
using namespace std;
struct heap
{
	int val,id;
	heap *l,*r;
	heap(){}
	heap(int v,int ID):val(v),id(ID),l(0),r(0){}
}pool[400001];
int tot=0,p[110001];
inline heap *new_node(int v,int id){return &(pool[tot++]=heap(v,id));}
heap *merge(heap *a,heap *b)
{
	if(!a)return b;
	if(!b)return a;
	if(a->val>b->val||(a->val==b->val&&a->id>b->id))swap(a,b);
	a->r=merge(a->r,b);
	p[a->r->id]=a->id;
	swap(a->l,a->r);
	return a;
}
heap *h[110001];
int n,m;
int find(int x){return p[x]==x?x:find(p[x]);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		h[i]=new_node(x,i);
		p[i]=i;
	}
	while(m--)
	{
		int op,x,y;
		scanf("%d%d",&op,&x);
		if(op==1)
		{
			scanf("%d",&y);
			int a=find(x),b=find(y);
			if(a!=b&&h[a]&&h[b])merge(h[a],h[b]);
		}
		else
		{
			int a=find(x);
			if(h[a])
			{
				printf("%d\n",h[a]->val);
				heap *u=h[a]->l,*v=h[a]->r;
				if(u)p[u->id]=u->id;
				if(v)p[v->id]=v->id;
				if(u&&v)merge(u,v);
				h[a]=0;
			}
			else puts("-1");
		}
	}
	return 0;
}
