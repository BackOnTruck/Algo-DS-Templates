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
inline void rotate(Treap *&o,int d)
{
	Treap *k=o->ch[d^1];o->ch[d^1]=k->ch[d];k->ch[d]=o;
	o->maintain();
	k->maintain();
	o=k;
}
void insert(Treap *&o,int x)
{
	if(!o)o=new_Treap(x);
	else
	{
		int d=o->cmp(x);
		insert(o->ch[d],x);
		if(o->ch[d]->r>o->r)rotate(o,d^1);
	}
	o->maintain();
}
void remove(Treap *&o,int x)
{
	if(o->v==x)
	{
		if(!o->ch[0])o=o->ch[1];
		else if(!o->ch[1])o=o->ch[0];
		else
		{
			int e=o->ch[0]->r>o->ch[1]->r;
			rotate(o,e);
			remove(o->ch[e],x);
		}
	}
	else remove(o->ch[o->cmp(x)],x);
	if(o)o->maintain();
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
