#include<cstdio>
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1,j;i<=n;i=j+1)
	{
		j=n/(n/i);
		ans+=n/i*(j-i+1);
	}
	printf("%d\n",ans);
}
