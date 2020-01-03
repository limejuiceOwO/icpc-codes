#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 2005
#define INF 100000005
using namespace std;

struct Thing {
	int a,b;
	bool operator <(const Thing &rhs) const { //因为a-1最小是-1，所以按a从大到小排序可以避免负体积（负体积一定不合法）
		return a>rhs.a;
	}
} thing[N];

int dp[N][N]; //考虑前i个，边数-点数+1=j
//边数-点数>=-1时合法
int main()
{
	int n;
	scanf("%d",&n);

	for(int i=0;i<n;i++) {
		scanf("%d%d",&thing[i].a,&thing[i].b);
	}
	sort(thing,thing+n);

	memset(dp,0x80,sizeof(dp));
	dp[0][1]=0;

	for(int i=0;i<n;i++) {
		int a=thing[i].a,b=thing[i].b;

		for(int j=0;j<=n;j++) {
			if(j+a-1>=0) dp[i+1][min(j+a-1,n)]=max(dp[i+1][min(j+a-1,n)],dp[i][j]+b); //因为j>=n时一定合法，所以不需要>n的状态
			dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
		}
	}

	int ans=0;
	for(int j=0;j<=n;j++) {
		ans=max(ans,dp[n][j]);
	}
	
	printf("%d\n",ans);
	return 0;
}