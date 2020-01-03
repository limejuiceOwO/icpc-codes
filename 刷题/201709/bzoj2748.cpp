//HAOI2012 音量调节 巨水的dp
//#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 55
#define M 1005
using namespace std;

char dp[N][M];

int main()
{
	int n,beginlvl,maxlvl;
	scanf("%d%d%d",&n,&beginlvl,&maxlvl);

	dp[0][beginlvl]=1;
	for(int i=1;i<=n;i++) {
		int c;
		scanf("%d",&c);
		for(int j=c;j<=maxlvl;j++) {
			dp[i][j]|=dp[i-1][j-c];
		}
		for(int j=0;j<=maxlvl-c;j++) {
			dp[i][j]|=dp[i-1][j+c];
		}
	}

	int ans=-1;
	for(int i=maxlvl;i>=0;i--) {
		if(dp[n][i]) {
			ans=i;
			break;
		}
	}
	printf("%d\n",ans);
	return 0;
}