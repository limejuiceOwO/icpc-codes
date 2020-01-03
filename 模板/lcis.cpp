#include <iostream>
#include <algorithm>
#define N 1005
using namespace std;

int l1[N],l2[N];
int dp[N][N];

int main()
{
	int n,m;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>l1[i];
	cin>>m;
	for(int i=0;i<m;i++)
		cin>>l2[i];

	for(int i=0;i<n;i++) {
		int mx=0;
		for(int j=0;j<m;j++) {
			if(l1[i]==l2[j]) {
				dp[i][j]=mx+1;
			} else {
				dp[i][j]= i>0 ? dp[i-1][j] : 0;
			}
			mx= i>0&&l1[i]>l2[j] ? max(mx,dp[i-1][j]) : mx;
		}
	}

	int ans=0;
	for(int i=0;i<m;i++)
		ans=max(ans,dp[n-1][i]);

	cout<<ans<<endl;

	return 0;
}