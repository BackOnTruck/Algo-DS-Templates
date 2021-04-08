#include<bits/stdc++.h>
using namespace std;
const double alpha=.7;
struct SGoat
{
	int v,s,cnt;
	SGoat *ch[2];
	SGoat(int x=0):v(x),s(1),cnt(1),ch{0,0}{}
	void maintain(){s=cnt+(ch[0]?ch[0]->s:0)+(ch[1]?ch[1]->s:0);}
}pool[300001];
int tot=0;
inline SGoat *new_SGoat(int x){return &(pool[tot++]=SGoat(x));}
inline int size(SGoat *o){return o?o->s:0;}
vector<SGoat*> v;
void get(SGoat *o)
{
	if(!o)return;
	SGoat *l=o->ch[0],*r=o->ch[1];
	o->ch[0]=o->ch[1]=0;
	o->s=o->cnt;
	get(l);
	if(o->cnt)v.push_back(o);
	get(r);
}
void build(SGoat *&o,int l,int r)
{
	if(l>r){o=0;return;}
	if(l==r){o=v[l];return;}
	int m=(l+r)/2;
	o=v[m];
	build(o->ch[0],l,m-1);
	build(o->ch[1],m+1,r);
	o->maintain();
}
inline void rebuild(SGoat *&o)
{
	v.clear();
	get(o);
	build(o,0,v.size()-1);
}
void insert(SGoat *&o,int x)
{
	if(!size(o)){o=new_SGoat(x);return;}
	if(max(size(o->ch[0]),size(o->ch[1]))>o->s*alpha)rebuild(o);
	if(o->v==x){o->cnt++;o->s++;return;}
	if(o->v>x)insert(o->ch[0],x);
	else insert(o->ch[1],x);
	o->maintain();
}
void remove(SGoat *&o,int x)
{
	if(o->v>x)remove(o->ch[0],x);
	else if(o->v<x)remove(o->ch[1],x);
	else o->cnt--;
	o->maintain();
}
int kth(SGoat *o,int k)
{
	if(!o||k<=0||k>o->s)return 0;
	int s=size(o->ch[0]);
	if(k<=s)return kth(o->ch[0],k);
	if(k<=s+o->cnt)return o->v;
	return kth(o->ch[1],k-s-o->cnt);
}
int Rank(SGoat *o,int x)
{
	if(!o)return 1;
	if(x<=o->v)return Rank(o->ch[0],x);
	return Rank(o->ch[1],x)+size(o->ch[0])+o->cnt;
}
inline int count(SGoat *o,int x)
{
	for(;;)
		if(!o)return 0;
		else if(o->v<x)o=o->ch[1];
		else if(o->v>x)o=o->ch[0];
		else return o->cnt;
}
int n,op,x;
SGoat *T=0;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&op,&x);
		if(op==1)insert(T,x);
		else if(op==2)remove(T,x);
		else if(op==3)printf("%d\n",Rank(T,x));
		else if(op==4)printf("%d\n",kth(T,x));
		else if(op==5)printf("%d\n",kth(T,Rank(T,x)-1));
		else printf("%d\n",kth(T,Rank(T,x)+count(T,x)));
	}
}
