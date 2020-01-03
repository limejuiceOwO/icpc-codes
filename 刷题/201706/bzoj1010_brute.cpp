#include <iostream>
#include <algorithm>
#define N 50005
using namespace std;

long long dp[N],sum[N];

long long sq(long long x)
{
	return x*x;
}

int main()
{
	int n,L;
	cin>>n>>L;
	for(int i=1;i<=n;i++) {
		cin>>sum[i];
		sum[i]+=sum[i-1];
	}

	for(int i=1;i<=n;i++) {
		dp[i]=(1LL<<62);
		for(int j=0;j<i;j++) {
			dp[i]=min(dp[i],dp[j]+sq(sum[i]-sum[j]+(i-j-1)-L));
		}
	}

	cout<<dp[n]<<endl;
	return 0;
}