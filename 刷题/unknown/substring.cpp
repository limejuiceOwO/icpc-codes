#include<bits/stdc++.h>
using namespace std;

long long dp[201][201];
long long f[201][201];
string str1,str2;
const long long M=1000000007;

int main()
{
	cin.sync_with_stdio(false);
  int n,m,kk;
  cin>>n>>m>>kk;
  cin.get();
  getline(cin,str1);
  getline(cin,str2);
  dp[0][0]=f[0][0]=1;
  for(int i=1;i<=n;i++) {
    for(int j=min(i,m);j>0;j--) {
      for(int k=min(j,kk);k>0;k--) {
	    if(str1[i-1]==str2[j-1]) {
	      	if(i==j) dp[j][k]=0;
	      	dp[j][k]=(dp[j][k]+f[j-1][k-1])%M;
		    f[j][k]=(j==k)?(dp[j][k]%M):((f[j-1][k]+dp[j][k])%M);
		} else {
			if(i==j) dp[j][k]=0;
			f[j][k]=dp[j][k];
		}
		//printf("%d %d %d %lld %lld\n",i,j,k,dp[j][k],f[j][k]);
      }
      f[j][0]=(str1[i-1]==str2[j-1])?f[j-1][0]:0;
    }
  }
  cout<<dp[m][kk]<<endl;
  return 0;
}
//orzorzorzorzorzorzorzorzorzorz
