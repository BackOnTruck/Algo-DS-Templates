#include<bits/stdc++.h>
using namespace std;
struct state
{
	state *p,*go[26];
	int val,sz,cnts;
	state(){}
	state(int value):p(0),val(value),sz(0),cnts(0){memset(go,0,sizeof go);}
}pool[2000001];
int tot=0;
vector<state*> node;
inline state *new_state(int v){node.push_back(&pool[tot]);return &(pool[tot++]=state(v));}
struct SAM
{
	state *root,*last;
	SAM(char *s){root=last=new_state(0);while(*s)append(*s++);}
	void append(char z)
	{
		int x=ID(z);
		state *p=last,*np=last=new_state(p->val+1);
		while(p&&!p->go[x])p->go[x]=np,p=p->p;
		if(!p){np->p=root;return;}
		state *q=p->go[x];
		if(p->val+1==q->val){np->p=q;return;}
		state *nq=new_state(p->val+1);
		memcpy(nq->go,q->go,sizeof q->go);
		nq->p=q->p;
		np->p=q->p=nq;
		while(p&&p->go[x]==q)p->go[x]=nq,p=p->p;
	}
	static int ID(char x){return x-'a';}
};
long long ans=0;
char s[1500001];
int main()
{
	scanf("%s",s);
	SAM sam(s);
	state *t=sam.root;
	for(int i=0;s[i];i++)
	{
		t=t->go[s[i]-'a'];
		t->sz++;
	}
	for(state *u:node)
		if(u->p)u->p->cnts++;
	queue<state*> q;
	for(state *u:node)
		if(!u->cnts)q.push(u);
	while(!q.empty())
	{
		state *u=q.front();q.pop();
		if(u->p)
		{
			u->p->sz+=u->sz;
			if(!--u->p->cnts)q.push(u->p);
		}
		if(u->sz!=1)ans=max(ans,1ll*u->sz*u->val);
	}
	printf("%lld\n",ans);
}
