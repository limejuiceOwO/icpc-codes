#include <iostream>
#include <algorithm>
#define N 15
#define NN 32773
using namespace std;

int map[N][N];
int dp[2][NN];

bool valid(int S,int i)
{
	for(int b=0;b<m;b++) {
		if(b>0&&S&(1<<b-1)&&S&(1<<b)) return false;
		if(map[i][b]&&S&(1<<b)) return false;
	}
	return true;
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cin>>map[i][j];
		}
	}
	int cur=1;
	for(int i=1;i<=n;i++) {
		int prev=cur^1;
		for(int S=(1<<m)-1;S;S--) {
			if(!valid(S,i)) continue;
			for(int T=(1<<m)-1;T;T--) {
				if(S&T||!valid(T,i-1)) continue;
				dp[cur][S]+=dp[prev][T];
			}
		}
	}
	cur^=1;
	int ans=0;
	for(int S=(1<<m)-1;S;S--) ans+=dp[cur][S];
	cout<<ans<<endl;
	return 0;
}