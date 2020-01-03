#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 2005
#define INF 100000005
using namespace std;

int dp[N][2*N]; //考虑前i个，边数-点数+N+1=j
//边数-点数>=-1时合法
int main()
{
	int n;
	scanf("%d",&n);

	memset(dp,0x80,sizeof(dp));
	dp[0][N+1]=0;

	for(int i=0;i<n;i++) {
		int a,b;
		scanf("%d%d",&a,&b);

		for(int j=0;j<=N+n;j++) {
			if(j+a-1>=0) dp[i+1][min(j+a-1,N+n)]=max(dp[i+1][min(j+a-1,N+n)],dp[i][j]+b); //因为j>=n时一定合法，所以不需要>n的状态
			dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
		}
	}

	int ans=0;
	for(int j=N;j<=N+n;j++) {
		ans=max(ans,dp[n][j]);
	}
	
	printf("%d\n",ans);
	return 0;
}