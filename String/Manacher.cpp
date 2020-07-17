#include<bits/stdc++.h>
using namespace std;
int r[27000001],m;
char t[27000001],s[27000001];
int main()
{
	scanf("%s",t);
	m=strlen(t);
	s[0]='@';
	for(int i=0;i<m;i++)s[2*i+1]=t[i],s[2*i+2]='$';
	s[2*m]=0;
	int top=0,n=2*m+1,p=0;
	r[0]=1;
	for(int i=1;i<n;i++)
		{
			if(top<i)r[i]=1;
			else if(top-i>=r[2*p-i])r[i]=r[2*p-i];
			else r[i]=top-i;	
			while(i-r[i]>=0&&i+r[i]<n)
				if(s[i-r[i]]==s[i+r[i]])r[i]++;
				else break;
			if(top<i+r[i]-1)top=i+r[i]-1,p=i;
		}
	int ans=0;
	for(int i=0;i<n;i++)
	{
		if(!isalpha(s[i-r[i]+1]))r[i]--;
		ans=max(ans,r[i]);
	}
	printf("%d\n",ans);
}
