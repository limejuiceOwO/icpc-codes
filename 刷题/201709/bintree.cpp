#include <iostream>
#include <algorithm>
#define N 3005
using namespace std;

int dp[N][N],s[N][N];
int arr[N],prefix[N];

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>arr[i];
	}

	sort(arr,arr+n);
	for(int i=0;i<n;i++) {
		dp[i][i]=prefix[i]=arr[i];
		s[i][i]=i;
		if(i) prefix[i]+=prefix[i-1];
	}

	for(int len=2;len<=n;len++) {
		for(int l=0;l<=n-len;l++) {
			int r=l+len-1,sum=prefix[r]-(l==0 ? 0 : prefix[l-1]);
			dp[l][r]=min(dp[l+1][r],dp[l][r-1])+sum;
			s[l][r]=(dp[l+1][r]<dp[l][r-1] ? l : r);
			for(int k=s[l][r-1];k<=s[l+1][r];k++) {
				if(dp[l][r]>dp[l][k-1]+dp[k+1][r]+sum) {
					dp[l][r]=dp[l][k-1]+dp[k+1][r]+sum;
					s[l][r]=k;
				}
			}
		}
	}

	cout<<dp[0][n-1]<<endl;
	return 0;
}