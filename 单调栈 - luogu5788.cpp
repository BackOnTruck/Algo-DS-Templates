#include<cstdio>
#include<stack>
using namespace std;
int n,a[4000001],ans[4000001];
stack<pair<int,int>> s;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=n;i;i--)
	{
		while(!s.empty()&&s.top().first<=a[i])s.pop();
		if(s.empty())ans[i]=0;
		else ans[i]=s.top().second;
		s.push({a[i],i});
	}
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	puts("");
}
