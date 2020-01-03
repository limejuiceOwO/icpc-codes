#include <iostream>
#include <algorithm>
#define N 1005
#define INF 1000000005
#define UPD(X,Y) ((X)=min(X,Y))
#define INI(X) ((X)=INF)
using namespace std;

int dp[N][N][2];
int w[N];

int main()
{
	int n,v;
	cin>>n>>v;
	for(int i=0;i<n;i++) {
		int d,ww;
		cin>>d>>ww;
		w[d]+=ww;
	}
	dp[0][0][0]=dp[0][0][1]=0;
	for(int i=0;i<v;i++) {
		for(int len=0;len<=i;len++) {//?
			int j=i+len;
			INI(dp[i][j][0]);
			INI(dp[i][j][1]);
			UPD(dp[i][j][1],dp[i][j-1][1]+w[j]);
			UPD(dp[i][j][0],dp[i-1][j][0]+w[i]);
			UPD(dp[i][j][1],dp[i][j-1][0]+w[j]*(j-i));
			UPD(dp[i][j][0],dp[i-1][j][1]+w[i]*(j-i));
		}
	}
	cout<<min(dp[v][n-v][0],dp[v][n-v][1])<<endl;
	return 0;
}
