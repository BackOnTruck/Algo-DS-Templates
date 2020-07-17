#include<bits/stdc++.h>
using namespace std;
struct heap
{
	int val,id;
	heap *l,*r;
	heap(){}
	heap(int v,int k):val(v),id(k),l(0),r(0){}
}pool[500001];
int p[110001],tot=0;
int find(int x){return p[x]==x?x:find(p[x]);}
heap *new_node(int val,int id){return &(pool[tot++]=heap(val,id));}
inline heap *merge(heap *a,heap *b)
{
	if(!a)return b;
	if(!b)return a;
	if(a->val>b->val||(a->val==b->val&&a->id>b->id))swap(a,b);
	b->r=a->l;a->l=b;
	p[b->id]=a->id;
	return a;
}
heap *merge(heap *c)
{
	if(!c||!c->r){if(c)p[c->id]=c->id;return c;}
	heap *a=c->r,*b=a->r;
	c->r=a->r=0;
	p[c->id]=c->id;
	p[a->id]=a->id;
	return merge(merge(c,a),merge(b));
}
heap *h[110001];
int main()
{
	int n,m;
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
				merge(h[a]->l);
				h[a]=0;
			}
			else puts("-1");
		}
	}
	return 0;
}
