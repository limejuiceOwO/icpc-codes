#include<iostream>
#include<algorithm>
using namespace std;

long long dp[40];
char seq[40];

//d(i,k)=max(d(l,k-1)*seq[l+1..i],i-1>=l>=k-1)
int main()
{
	int n,nk;
	cin>>n>>nk;
	cin.get();
	cin>>seq[0];
	seq[0]-='0';
	dp[0]=seq[0];
	for(int i=1;i<n;i++) {
		cin>>seq[i];
		seq[i]-='0';
		dp[i]=dp[i-1]*10+seq[i];
	}
	for(int k=1;k<=nk;k++)
		  for(int i=n-1;i>=k;i--) {
			int num=seq[i],power=10;
				dp[i]=0;
				for(int l=i-1;l>=k-1;l--) {
					dp[i]=max(dp[i],dp[l]*num);
					num+=seq[l]*power;
					power*=10;
				}
			}
	cout<<dp[n-1]<<endl;
	return 0;
}
