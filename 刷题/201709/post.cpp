#include <iostream>
#include <algorithm>
#define N 2005
#define INF 10000005
using namespace std;

int arr[N],dp[N][N],cost[N][N];
int n;

void solve(int j,int l=0,int r=n-1,int lb=0,int rb=n-1)
{
	if(l>r) return;
	int mid=(l+r)>>1,best=0;
	dp[j][mid]=INF;
	for(int i=lb;i<=min(mid-1,rb);i++) {
		if(dp[j][mid]>dp[j-1][i]+cost[i+1][mid]) {
			dp[j][mid]=dp[j-1][i]+cost[i+1][mid];
			best=i;
		}
	}
	solve(j,l,mid-1,lb,best);
	solve(j,mid+1,r,best,rb);
}

int main()
{
	ios::sync_with_stdio(false);

	int m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		cin>>arr[i];
	}

	sort(arr,arr+n);

	for(int i=0;i<n;i++) {
		for(int j=1;i+j<n&&i-j>=0;j++) {
			cost[i-j][i+j]=cost[i-j+1][i+j-1]+arr[i+j]-arr[i-j];
		}
		cost[i][i+1]=arr[i+1]-arr[i];
		for(int j=1;i+j+1<n&&i-j>=0;j++) {
			cost[i-j][i+j+1]=cost[i-j+1][i+j]+arr[i+j+1]-arr[i-j];
		}
	}

	for(int i=0;i<n;i++) {
		dp[1][i]=cost[0][i];
	}
	for(int j=2;j<=m;j++) {
		solve(j);
	}
	cout<<dp[m][n-1]<<endl;
	return 0;
}