#include <iostream>
#include <algorithm>
#include <cmath>
#define N 1000005
using namespace std;

int arr[N];
int dp[N];
int que[N],idx[N],mn[N];

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>arr[n-i-1];
	}

	idx[0]=0;
	que[0]=mn[0]=dp[0]=arr[0];
	int tail=1;
	for(int i=1;i<n;i++) {
		dp[i]=abs(arr[i]-i);
		int key=i-arr[i]-1;
		if(key<i) {
			dp[i]=min(dp[i],que[lower_bound(idx,idx+tail,key)-idx]-key);
		}
		if(key>=0) {
			dp[i]=min(dp[i],mn[min(i-1,key)]+key);
		}
		while(tail&&que[tail-1]>=dp[i]+i) tail--;
		que[tail]=dp[i]+i;
		idx[tail++]=i;
		mn[i]=min(mn[i-1],dp[i]-i);
	}

	cout<<dp[n-1]<<endl;
	return 0;
}