#include<bits/stdc++.h>
using namespace std;
struct state
{
	state *p,*go[27];
	int len,cnt;
	state(){}
	state(int length,state *fail,int count=0):p(fail),len(length),cnt(count){memset(go,0,sizeof go);}
}pool[300001];
int tot=0;
inline state *new_state(int length,state *fail,int count=0){return &(pool[tot++]=state(length,fail,count));}
struct PAM
{
	state *oroot,*eroot,*last;
	char s[400001];
	int length;
	PAM(char *c):oroot(new_state(-1,0)),eroot(new_state(0,oroot)),last(eroot),length(0)
	{
		oroot->p=oroot;
		while(*c)extend(*c),s[length]=*c++;
	}
	static int ID(char x){return x-'a';}
	// 这里cnt统计的是每个结点对应的回文串个数。如果需要逐个添加字符，计算后缀回文串的个数，
	// 只需在extend()最后加上q->cnt=q->p->cnt+1，并将p->go[x]->cnt++删去即可
	void extend(char ch)
	{
		int x=ID(s[++length]=ch);
		state *p=last;
		while(s[length-p->len-1]!=ch)p=p->p;
		if(p->go[x]){p->go[x]->cnt++;last=p->go[x];return;}
		else p->go[x]=new_state(p->len+2,0,1);
		state *q=last=p->go[x];
		p=p->p;
		while(s[length-p->len-1]!=ch)p=p->p;
		q->p=(q->len==1?eroot:p->go[x]);
	}
};
char s[200001];
int main()
{
	scanf("%s",s);
	PAM pam(s);
}
