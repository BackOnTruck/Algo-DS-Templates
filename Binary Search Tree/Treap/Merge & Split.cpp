#include<bits/stdc++.h>
using namespace std;
struct Treap
{
	int v,r,s;
	Treap *ch[2];
	Treap(){}
	Treap(int x):v(x),r(rand()),s(1),ch{0,0}{}
	int cmp(int x)const{return x>=v;}
	void maintain()
	{
		s=1;
		if(ch[0])s+=ch[0]->s;
		if(ch[1])s+=ch[1]->s;
	}
}pool[300001];
int tot=0;
inline Treap *new_Treap(int x){return &(pool[tot++]=Treap(x));}
void split(Treap *o,int v,Treap *&l,Treap *&r)
{
	if(!o){l=r=0;return;}
	if(o->v<=v)l=o,split(o->ch[1],v,l->ch[1],r),l->maintain();
	else r=o,split(o->ch[0],v,l,r->ch[0]),r->maintain();
}
Treap *merge(Treap *l,Treap *r)
{
	if(!l)return r;
	if(!r)return l;
	Treap *o;
	if(l->r<r->r)o=l,o->ch[1]=merge(l->ch[1],r);
	else o=r,o->ch[0]=merge(l,r->ch[0]);
	o->maintain();
	return o;
}
inline void insert(Treap *&o,int v)
{
	Treap *l,*r;
	split(o,v,l,r);
	o=merge(merge(l,new_Treap(v)),r);
}
inline void remove(Treap *&o,int v)
{
	Treap *l,*m,*r,*t;
	split(o,v-1,l,t);
	split(t,v,m,r);
	m=merge(m->ch[0],m->ch[1]);
	o=merge(merge(l,m),r);
}
int kth(Treap *o,int k)
{
	if(!o||k<=0||k>o->s)return 0;
	int s=(!o->ch[0]?0:o->ch[0]->s);
	if(k==s+1)return o->v;
	if(k<=s)return kth(o->ch[0],k);
	return kth(o->ch[1],k-s-1);
}
int Rank(Treap *o,int x)
{
	if(!o)return 1;
	if(x<=o->v)return Rank(o->ch[0],x);
	return Rank(o->ch[1],x)+(o->ch[0]?o->ch[0]->s:0)+1;
}
int from(Treap *o,int x)
{
	if(!o)return -(1<<30);
	if(o->v<x)return max(o->v,from(o->ch[1],x));
	return from(o->ch[0],x);
}
int to(Treap *o,int x)
{
	if(!o)return 1<<30;
	if(o->v>x)return min(o->v,to(o->ch[0],x));
	return to(o->ch[1],x);
}
void print(Treap *o)
{
	if(!o)return;
	print(o->ch[0]);
	printf("%d ",o->v);
	print(o->ch[1]);
}
int n,op,x;
Treap *T;
int main()
{
	srand(time(0));
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&op,&x);
		if(op==1)insert(T,x);
		else if(op==2)remove(T,x);
		else if(op==3)printf("%d\n",Rank(T,x));
		else if(op==4)printf("%d\n",kth(T,x));
		else if(op==5)printf("%d\n",from(T,x));
		else printf("%d\n",to(T,x));
	}
}
