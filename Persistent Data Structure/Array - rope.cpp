#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
rope<int> *s[1000007]={new rope<int>()};
inline int read()
{
	int f=1,r=0;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){r=r*10+c-'0';c=getchar();}
	return f*r;
}
int main()
{
	int n=read(),m=read();
	s[0]->append(0);
	for(int i=1;i<=n;i++)s[0]->append(read());
	for(int i=1;i<=m;i++)
	{
		int v=read(),op=read(),p=read();
		s[i]=new rope<int>(*s[v]);
		if(op==1)s[i]->replace(p,read());
		else printf("%d\n",s[i]->at(p));
	}
}

//: Explanation
//& Persistent Array, supports modifying and querying single value from history version.
//& queries:
//^ version 1 pos value: Modifying
//^ version 2 pos: Querying
//& submitted at luogu 3919
