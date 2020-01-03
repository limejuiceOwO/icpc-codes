#include <iostream>
#include <algorithm>
#include <cstring>
#define N 20
#define M 65541
using namespace std;

int G[N][N],dp[N][M];

int main()
{
	int n,m,st;
	cin>>n>>m>>st;
	for(int i=0;i<m;i++) {
		int u,v,d;
		cin>>u>>v>>d;
		G[u][v]=d;
	}
	memset(dp,0x7f,sizeof(dp));
	dp[st][1<<st]=0;
	for(int u=1;u<=n;u++) {
		for(int j=1;j<(1<<n);j++) {
			for(int v=1;v<=n;v++) {
				if(u!=v&&G[u][v]&&!(j&(1<<v))) {
					dp[v][j|(1<<v)]=min(dp[u][j]+G[u][v],dp[v][j|(1<<v)]);
				}
			}
		}
	}
	cout<<dp[st][(1<<n)-1]<<endl;
	return 0;
}