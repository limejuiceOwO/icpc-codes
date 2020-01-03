#include <iostream>
#include <algorithm>
#include <cstring>
#define N 205
using namespace std;

bool dp[2][2*N*N];
int a[N],b[N];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i]>>b[i];
		if(a[i]<b[i]) swap(a[i],b[i]);
	}

	dp[0][N*N]=true;
	int lb=0,rb=0;
	for(int i=1;i<=n;i++) {
		int nxt=i&1,cur=nxt^1;
		memset(dp[nxt],0,sizeof(dp[0]));
		for(int j=lb;j<=rb;j++) {
			dp[nxt][j+a[i]+N*N]|=dp[cur][j+N*N];
			dp[nxt][j-b[i]+N*N]|=dp[cur][j+N*N];
		}
		lb-=b[i],rb+=a[i];
	}

	int ans=1000000005;
	for(int i=lb;i<=rb;i++) {
		if(dp[n&1][i+N*N]) {
			ans=min(ans,max(abs(i),abs(-lb-rb+i)));
		}
	}
	cout<<ans<<endl;
	return 0;
}