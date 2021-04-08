#include<cstdio>
const int lim=25;
struct trie
{
	int ch[1<<24][2],s[1<<24],n;
	trie():n(0){newnode();}
	int newnode(){n++;ch[n][0]=ch[n][1]=s[n]=0;return n;}
	void add(int x,int d)
	{
		int u=1;
		for(int i=lim;i>=0;i--)
		{
			int &v=ch[u][(x>>i)&1];
			if(!v)v=newnode();
			s[u=v]+=d;
		}
	}
	int count(int x)
	{
		int u=1;
		for(int i=lim;i>=0;i--)u=ch[u][(x>>i)&1];
		return s[u];
	}
	int kth(int k)
	{
		int u=1,ans=0;
		for(int i=lim;i>=0;i--)
		{
			int l=ch[u][0],r=ch[u][1];
			if(s[l]<k)k-=s[l],ans^=1<<i,u=r;
			else u=l;
		}
		return ans;
	}
	int rank(int x) // not actual rank - # of numbers smaller than x
	{
		int u=1,ans=0;
		for(int i=lim;i>=0;i--)
			if(x&(1<<i))ans+=s[ch[u][0]],u=ch[u][1];
			else u=ch[u][0];
		return ans;
	}
}T;
const int num=10000000;
int main()
{
	int n,op,x;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&op,&x);
		x+=num;
		if(op==1)T.add(x,1);
		else if(op==2)T.add(x,-1);
		else if(op==3)printf("%d\n",T.rank(x)+1);
		else if(op==4)printf("%d\n",T.kth(x-num)-num);
		else if(op==5)printf("%d\n",T.kth(T.rank(x))-num);
		else printf("%d\n",T.kth(T.rank(x)+1+T.count(x))-num);
	}
}
