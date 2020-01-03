#include <iostream>
#include <algorithm>
#define N 105
#define M 5
using namespace std;

char buf[M+5];
int dp[N][(1<<M)+5],board[N];

int main() 
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>buf;
		for(int j=0;j<M;j++) {
			board[i]=(board[i]<<1)|((buf[j]-'0')&1);
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=0;j<(1<<M);j++) {
			dp[i][j]=1000000;
			for(int k=j;k;k=(k-1)&j) {
				dp[i][j]=min(dp[i][j],dp[i-1][k]);
			}
			for(int k=j&(~board[i-1]);k;k>>=1) dp[i][j]+=(k&1);
		}
	}
	int ans=1000000;
	for(int i=0;i<(1<<M);i++) {
		ans=min(ans,dp[n][i]);
	}
	cout<<ans<<endl;
	return 0;
}