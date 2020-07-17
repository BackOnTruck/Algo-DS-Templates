#include<bits/stdc++.h>
using namespace std;
struct Splay
{
	int v,f,s;
	Splay *ch[2],*p;
	Splay(){}
	Splay(int x,Splay *par):v(x),f(0),s(1),ch{0,0},p(par){}
	void pushdown()
	{
		if(!f)return;
		f=0;swap(ch[0],ch[1]);
		if(ch[0])ch[0]->flip();
		if(ch[1])ch[1]->flip();
	}
	void maintain()
	{
		s=1;
		if(ch[0])s+=ch[0]->s;
		if(ch[1])s+=ch[1]->s;
	}
	void flip(){f^=1;}
	int re(){return p->ch[1]==this;}
}pool[300001],*T=0;
int tot=0;
inline Splay *new_Splay(int x,Splay *p){return &(pool[tot++]=Splay(x,p));}
inline void turn_up(Splay *o)
{
	o->p->pushdown();
	int d=o->re(),e=(o->p->p?o->p->re():1);
	Splay *p=o->p;
	o->p=p->p;
	p->p=o;
	if(o->ch[d^1])o->ch[d^1]->p=p;
	p->ch[d]=o->ch[d^1];
	o->ch[d^1]=p;
	if(o->p)o->p->ch[e]=o;
	p->maintain();
	o->maintain();
}
inline void rotate(Splay *o)
{
	if(o->re()!=o->p->re())turn_up(o);
	else turn_up(o->p);
	turn_up(o);
}
inline Splay *splay(Splay *o)
{
	if(!o->p)return o;
	while(o->p&&o->p->p)rotate(o);
	if(o->p)turn_up(o);
	return o;
}
Splay *kth(Splay *o,int k)
{
	if(!o||k<=0||k>o->s)return 0;
	o->pushdown();
	int s=(!o->ch[0]?0:o->ch[0]->s);
	if(k==s+1)return o;
	if(k<=s)return kth(o->ch[0],k);
	return kth(o->ch[1],k-s-1);
}
void build(Splay *&o,Splay *p,int l,int r)
{
	if(l>r)return;
	if(l==r){o=new_Splay(l,p);return;}
	int m=(l+r)/2;
	o=new_Splay(m,p);
	build(o->ch[0],o,l,m-1);
	build(o->ch[1],o,m+1,r);
	o->maintain();
}
int n,m,l,r;
void print(Splay *o)
{
	if(!o)return;
	o->pushdown();
	print(o->ch[0]);
	if(o->v&&o->v<=n)printf("%d ",o->v);
	print(o->ch[1]);
}
int main()
{
	scanf("%d%d",&n,&m);
	build(T,0,0,n+1);
	while(m--)
	{
		scanf("%d%d",&l,&r);r+=2;
		T=splay(kth(T,l));
		T->pushdown();
		T->ch[1]->p=0;
		T->ch[1]=splay(kth(T->ch[1],r-l));
		T->ch[1]->pushdown();
		T->ch[1]->p=T;
		T->ch[1]->ch[0]->flip();
	}
	print(T);puts("");
}
