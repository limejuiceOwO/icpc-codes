//dp(i,j,k,l):-长度i，和为j，乘d和为k(不算进位)，进位l的最小数 (d<10)
//dp(i,j,k,l)+m*10^i+1->dp(i+1,j+m,k+sum(d*m+l),(d*m+l)/10^i)

#include <iostream>
#include <algorithm>
#include <cstring>
#define N 20
#define UPD(A,B) ((A)=min(A,B))
using namespace std;

long long dp[N][9*N][9*N][10];

int main()
{
	int n,d,s1,s2;
	cin>>n>>s1>>s2>>d;

	long long pow=1;
	memset(dp,0x3f,sizeof(dp));
	dp[0][0][0][0]=0;
	for(int i=0;i<n;i++,pow*=10) {
		for(int j=0;j<=9*i;j++) {
			for(int k=0;k<=9*i;k++) {
				for(int l=0;l<10;l++) {
					for(int m=(i==n-1 ? 1 : 0);m<10;m++) {
						UPD(dp[i+1][j+m][k+(d*m+l)%10][(d*m+l)/10],dp[i][j][k][l]+pow*m);
					}
				}
			}
		}
	}

	cout<<dp[n][s1][s2][0]<<endl;
	return 0;
}