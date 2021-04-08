#include<bits/stdc++.h>
using namespace std;
struct Splay
{
	int v,s;
	Splay *ch[2],*p;
	Splay(){}
	Splay(int x,Splay *par):v(x),s(1),ch{0,0},p(par){}
	void maintain()
	{
		s=1;
		if(ch[0])s+=ch[0]->s;
		if(ch[1])s+=ch[1]->s;
	}
	int re(){return p->ch[1]==this;}
}pool[300001],*T=0;
int tot=0;
inline Splay *new_Splay(int x,Splay *p){return &(pool[tot++]=Splay(x,p));}
inline void turn_up(Splay *o)
{
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
inline void insert(Splay *&o,int x)
{
	if(!o)o=new_Splay(x,0);
	else for(;;)
	{
		int d=(o->v<=x);
		if(o->ch[d])o=o->ch[d];
		else
		{
			o->ch[d]=new_Splay(x,o);
			o->maintain();
			o=o->ch[d];
			splay(o);
			return;
		}
	}
}
int kth(Splay *o,int k)
{
	if(!o||k<=0||k>o->s)return 0;
	int s=(!o->ch[0]?0:o->ch[0]->s);
	if(k==s+1)return o->v;
	if(k<=s)return kth(o->ch[0],k);
	return kth(o->ch[1],k-s-1);
}
int Rank(Splay *o,int x)
{
	if(!o)return 1;
	if(x<=o->v)return Rank(o->ch[0],x);
	return Rank(o->ch[1],x)+(o->ch[0]?o->ch[0]->s:0)+1;
}
int from(Splay *o,int x)
{
	if(!o)return -(1<<30);
	if(o->v<x)return max(o->v,from(o->ch[1],x));
	return from(o->ch[0],x);
}
int to(Splay *o,int x)
{
	if(!o)return 1<<30;
	if(o->v>x)return min(o->v,to(o->ch[0],x));
	return to(o->ch[1],x);
}
Splay *find(Splay *o,int x)
{
	for(;;)
		if(o->v<x)o=o->ch[1];
		else if(o->v>x)o=o->ch[0];
		else return o;
}
void remove(Splay *&o,int x)
{
	Splay *p=find(o,x);
	splay(p);
	Splay *l=p->ch[0],*r=p->ch[1];
	if(!l&&!r)o=0;
	else if(!l)r->p=0,o=r;
	else if(!r)l->p=0,o=l;
	else
	{
		l->p=0;
		while(l->ch[1])l=l->ch[1];
		splay(l);
		l->ch[1]=r;
		o=r->p=l;
		o->maintain();
	}
}
int n,op,x;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&op,&x);
		if(op==1)insert(T,x);
		else if(op==2)remove(T,x);
		else if(op==3)
		{
			int k=Rank(T,x);
			printf("%d\n",k);
			T=splay(find(T,x));
		}
		else{int p=(op==4?kth(T,x):(op==5?from(T,x):to(T,x)));printf("%d\n",p);T=splay(find(T,p));}
	}
}
