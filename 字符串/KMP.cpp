#include<cstdio>
#include<cstring>
int f[100001];
void getfail(char *p)
{
	int m=strlen(p);
	f[0]=f[1]=0;
	for(int i=1;i<m;i++)
	{
		int j=f[i];
		while(j&&p[i]!=p[j])j=f[j];
		f[i+1]=p[i]==p[j]?j+1:0;
	}
}
int find(char *a,char *b)
{
	int n=strlen(a),m=strlen(b),j=0;
	getfail(b);
	for(int i=0;i<n;i++)
	{
		while(j&&a[i]!=b[j])j=f[j];
		if(a[i]==b[j])j++;
		if(j==m)return i-m+1;
	}
	return -1;
}
char a[200000],b[200000];
int main()
{
	scanf("%s%s",a,b);
	int ans=find(a,b);
	if(ans!=-1)printf("Found at %d\n%s\n%*c%*c\n",ans,a,ans+1,'^',strlen(b)-1,'^');
	else printf("Not Found\n");
	return 0;
}
