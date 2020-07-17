#include<bits/stdc++.h>
using namespace std;
struct state
{
	int match,count,reach;
	state *fail,*go[26];
	state():match(0),count(0),reach(0),fail(0),go{}{}
}alloc[1000001];
vector<state*> v;
int tot=0;
inline state *new_node(){state *x=v.back();*x=state();v.pop_back();return x;}
inline void free_node(state *x){v.push_back(x);}
struct ACAM
{
	state *root;
	int sz;
	ACAM():root(new_node()),sz(0){}
	void insert(char *x)
	{
		state *s=root;
		while(*x)
		{
			int id=*x++-'a';
			if(!s->go[id])s->go[id]=new_node();
			s=s->go[id];
		}
		s->match++;sz++;
	}
	void getfail()
	{
		root->fail=root;
		queue<state*> q;
		for(int i=0;i<26;i++)
			if(root->go[i])root->go[i]->fail=root,q.push(root->go[i]);
		while(!q.empty())
		{
			state *u=q.front();q.pop();
			u->count=u->match+u->fail->count;
			for(int i=0;i<26;i++)
				if(u->go[i])
				{
					q.push(u->go[i]);
					state *w=u->fail;
					while(w!=root&&!w->go[i])w=w->fail;
					state *Fail=(w->go[i]?w->go[i]:root);
					u->go[i]->fail=Fail;
				}
		}
	}
}acam;
int n;
char s[1100001];
int main()
{
	scanf("%d",&n);
	ACAM ac;
	while(n--)scanf("%s",s),ac.insert(s);
	ac.getfail();
	state *u=ac.root;
	scanf("%s",s);
	int ans=0;
	for(int i=0;s[i];i++)
	{
		int id=s[i]-'a';
		while(u!=ac.root&&!u->go[id])u=u->fail;
		if(u->go[id])
		{
			u=u->go[id];
			u->reach++;
		}
	}
	printf("%d\n",ans);
}
