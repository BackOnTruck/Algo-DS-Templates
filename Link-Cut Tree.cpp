#include<bits/stdc++.h>
using namespace std;
struct Splay
{
	int v,f,s;
	Splay *ch[2],*p;
	Splay(){}
	Splay(int x,Splay *par):v(x),f(0),s(x),ch{0,0},p(par){}
	void pushdown()
	{
		if(!f)return;
		f=0;
		if(ch[0])ch[0]->flip();
		if(ch[1])ch[1]->flip();
	}
	void maintain(){s=v^(ch[0]?ch[0]->s:0)^(ch[1]?ch[1]->s:0);}
	void flip(){f^=1;swap(ch[0],ch[1]);}
	int re(){return !p?-2:p->ch[1]==this?1:p->ch[0]==this?0:-1;}
}pool[800001];
int tot=0;
inline Splay *new_Splay(int x,Splay *p){return &(pool[tot++]=Splay(x,p));}
inline void turn_up(Splay *o)
{
	o->p->pushdown();o->pushdown();
	int d=o->re(),e=o->p->re();
	Splay *p=o->p;o->p=p->p;p->p=o;
	if(o->ch[d^1])o->ch[d^1]->p=p;
	p->ch[d]=o->ch[d^1];
	o->ch[d^1]=p;
	if(o->p&&e>=0)o->p->ch[e]=o;
	p->maintain();o->maintain();
}
inline void rotate(Splay *o){turn_up(o->re()!=o->p->re()?o:o->p);turn_up(o);}
inline void splay(Splay *o){while(o->re()>=0)o->p->re()>=0?rotate(o):turn_up(o);}
inline void access(Splay *o){for(Splay *x=0;o;x=o,o=o->p)splay(o),o->pushdown(),o->ch[1]=x,o->maintain();}
inline void makeroot(Splay *o){access(o);splay(o);o->flip();}
inline Splay *findroot(Splay *o)
{
	access(o);splay(o);
	for(;;)
	{
		o->pushdown();
		if(!o->ch[0])break;
		o=o->ch[0];
	}
	return splay(o),o;
}
inline void split(Splay *x,Splay *y){makeroot(x);access(y);splay(y);}
inline void link(Splay *x,Splay *y)
{
	makeroot(x);
	if(findroot(y)!=x)x->p=y;
}
inline void cut(Splay *x,Splay *y)
{
	makeroot(x);
	if(findroot(y)==x&&y->p==x&&!y->ch[0])y->p=x->ch[1]=0,x->maintain();
}
Splay *T[350001];
int n,m,v;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&v),T[i]=new_Splay(v,0);
	while(m--)
	{
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		if(!op)split(T[x],T[y]),printf("%d\n",T[y]->s);
		else if(op==1)link(T[x],T[y]);
		else if(op==2)cut(T[x],T[y]);
		else splay(T[x]),T[x]->v=y,T[x]->maintain();
	}
}
