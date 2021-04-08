#include<bits/stdc++.h>
#define rank fuck
using namespace std;
struct state
{
	state *p,*go[26],*son[26];
	int val,sz,pos,f;
	state(){}
	state(int value,int posit,bool x):p(0),val(value),sz(0),pos(posit),f(x){memset(go,0,sizeof go);memset(son,0,sizeof son);}
}pool[220001];
int tot=0,sa[110001],rank[110001],h[110001],cur=0;
inline state *new_state(int v,int p,bool x){return &(pool[tot++]=state(v,p,x));}
struct SAM
{
	state *root,*last;
	string s,rev;
	SAM(){}
	SAM(char *S):s(S),rev(s){reverse(rev.begin(),rev.end());root=last=new_state(0,0,0);for(int i=0;S[i];i++)append(S[i],s.size()-i-1);build_right();}
	void append(char z,int pos)
	{
		int x=z-'a';
		state *p=last,*np=last=new_state(p->val+1,pos,1);
		while(p&&!p->go[x])p->go[x]=np,p=p->p;
		if(!p){np->p=root;return;}
		state *q=p->go[x];
		if(p->val+1==q->val){np->p=q;return;}
		state *nq=new_state(p->val+1,q->pos,0);
		memcpy(nq->go,q->go,sizeof q->go);
		nq->p=q->p;
		np->p=q->p=nq;
		while(p&&p->go[x]==q)p->go[x]=nq,p=p->p;
	}
	void build_right()
	{
		state *t=root;
		for(char c:s)t=t->go[c-'a'],t->sz++;
		for(int i=tot-1;i>=0;i--)
		{
			state *u=pool+i;
			if(u->p)
			{
				u->p->sz+=u->sz;
				u->p->son[rev[u->pos+u->p->val]-'a']=u;
			}
		}
	}
};
void dfs(state *s)
{
	if(!s)return;
	if(s->f)sa[rank[s->pos]=cur++]=s->pos;
	for(int i=0;i<26;i++)dfs(s->son[i]);
}
char s[110001];
int n;
int main()
{
	scanf("%s",s);
	n=strlen(s);
	reverse(s,s+n);
	SAM rev(s);
	dfs(rev.root);
	reverse(s,s+n);
	for(int i=0,k=0;i<n;i++,k--)
		if(rank[i])
		{
			int j=sa[rank[i]-1];
			if(k<0)k=0;
			while(i+k<n&&j+k<n&&s[i+k]==s[j+k])k++;
			h[rank[i]]=k;
		}
	for(int i=0;i<n;i++)printf("%d ",sa[i]+1);
	puts("");
	for(int i=1;i<n;i++)printf("%d ",h[i]);
	puts("");
}
