#include<bits/stdc++.h>
using namespace std;
struct SA
{
	int rank[1100011],sa[1100011],h[1100011],Cnt[1100011],*cnt=Cnt+2,first[1100011],second[1100011],buf[1100011],v[1100011],f[18][1100011],lg2[1100011],N;
	SA(char *s,int n)
	{
		N=n;
		for(int i=0;i<n;i++)v[i]=s[i];
		sort(v,v+n);
		int *x=unique(v,v+n);
		memset(rank,-1,sizeof rank);
		for(int i=0;i<n;i++)rank[i]=lower_bound(v,x,s[i])-v;
		for(int t=1;t<=n;t<<=1)
		{
			for(int i=0;i<n;i++)first[i]=rank[i],second[i]=rank[i+t];
			fill(cnt,cnt+n,0);
			for(int i=0;i<n;i++)cnt[second[i]]++;
			for(int i=0;i<n;i++)cnt[i]+=cnt[i-1];
			for(int i=0;i<n;i++)buf[n-1- --cnt[second[i]]]=i;
			fill(cnt,cnt+n,0);
			for(int i=0;i<n;i++)cnt[first[i]]++;
			for(int i=0;i<n;i++)cnt[i]+=cnt[i-1];
			for(int j=0;j<n;j++)sa[--cnt[first[buf[j]]]]=buf[j];
			bool end=1;
			for(int j=0,last=-1;j<n;j++)
			{
				int i=sa[j];
				if(last==-1)rank[i]=0;
				else if(first[i]==first[last]&&second[i]==second[last])rank[i]=rank[last],end=0;
				else rank[i]=rank[last]+1;
				last=i;
			}
			if(end)break;
		}
		for(int i=0,k=0;i<n;i++,k--)
			if(rank[i])
			{
				int j=sa[rank[i]-1];
				if(k<0)k=0;
				while(i+k<n&&j+k<n&&s[i+k]==s[j+k])k++;
				h[rank[i]]=k;
			}
		for(int i=1;i<=n;i++)
			for(int j=0;;j++)
				if((1<<(j+1))>i){lg2[i]=j;break;}
		for(int i=0;i<n;i++)f[0][i]=h[i];
		for(int i=1;i<18;i++)
			for(int j=0;j<n;j++)f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	}
	int query(int x,int y)
	{
		if(x==y)return N-x;
		int l=rank[x],r=rank[y];
		if(l>r)swap(l,r);
		l++;
		int len=lg2[r-l+1];
		return min(f[len][l],f[len][r-(1<<len)+1]);
	}
};
char s[2000011];
int main()
{
	scanf("%s",s);
	int n=strlen(s);
	SA sa(s,n);
	for(int i=0;i<n;i++)printf("%d ",sa.sa[i]+1);
	puts("");
	for(int i=1;i<n;i++)printf("%d ",sa.h[i]);
	puts("");
	return 0;
}
