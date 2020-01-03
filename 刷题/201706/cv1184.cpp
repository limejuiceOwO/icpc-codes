#include <iostream>
#include <cstring>
#define M 70
#define P 100003
using namespace std;

int dp[2][M];

void add(int &a,int b)
{
	a=(a+b)%P;
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m;

	int prev=0;
	dp[0][(1<<n)-1]=1; //假设最上面还有一行，全部被填充

	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {

			int cur=prev^1;
			memset(dp[cur],0,sizeof(dp[0]));

			for(unsigned int s=0;s<(1<<n);s++) { //dp(i,j,S):-i行j列，边缘状态为S

				if(!(s&(1<<j))) { //不放
					dp[cur][s]=dp[prev][s|(1<<j)];
					continue;
				}

				if(j>0&&(s&(1<<(j-1)))) add(dp[cur][s],dp[prev][s&~(1<<(j-1))]); //横放
				if(i>0) add(dp[cur][s],dp[prev][s&~(1<<j)]); //竖放
			}

			prev=cur;

		}
	}

	cout<<dp[prev][(1<<n)-1]<<endl;
	return 0;
}