#include<iostream>
#include<algorithm>
using namespace std;

long long dp[40][7];
char seq[40];

//d(i,k)=max(d(l,k-1)*seq[l+1..i],i-1>=l>=k-1)
int main()
{
	int n,nk;
	cin>>n>>nk;
	cin.get();
	for(int i=0;i<n;i++) {
		cin>>seq[i];
		seq[i]-='0';
	}
	dp[0][0]=seq[0];
	for(int i=1;i<n;i++)
		 for(int k=min(i,nk);k>=0;k--) {
			int num=seq[i],power=10;
			if(k==0)
				dp[i][0]=dp[i-1][0]*10+num;
			else
				for(int l=i-1;l>=k-1;l--) {
					dp[i][k]=max(dp[i][k],dp[l][k-1]*num);
					num+=seq[l]*power;
					power*=10;
				}
		}
	cout<<dp[n-1][nk]<<endl;
	return 0;
}
