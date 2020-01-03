#include <iostream>
#include <algorithm>
#include <vector>
#define N 105
using namespace std;

vector<pair<int,int> > G[N];
int ch[N][2],w[N][2],size[N];
int dp[N][N];

void dfs(int u,int fa)
{
	size[u]=1;
	for(unsigned int i=0,cnt=0;i<G[u].size();i++) {
		int v=G[u][i].first;
		if(v==fa) continue;
		w[u][cnt]=G[u][i].second;
		dfs(ch[u][cnt++]=v,u);
		size[u]+=size[v];
	}
}

void solve(int u)
{
	if(ch[u][0]) solve(ch[u][0]);
	if(ch[u][1]) solve(ch[u][1]);
	for(int k=1;k<size[u];k++) {
		for(int kk=0;kk<size[ch[u][0]];kk++) {
			if(k-kk-2>=0&&k-kk-2<size[ch[u][1]])
			dp[u][k]=max(dp[u][k],dp[ch[u][0]][kk]+dp[ch[u][1]][k-kk-2]+w[u][0]+w[u][1]);
		}
		if(k-1<size[ch[u][0]]) dp[u][k]=max(dp[u][k],dp[ch[u][0]][k-1]+w[u][0]);
		if(ch[u][1]&&k-1<size[ch[u][1]]) dp[u][k]=max(dp[u][k],dp[ch[u][1]][k-1]+w[u][1]);
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n-1;i++) {
		int x,y,ww;
		cin>>x>>y>>ww;
		G[x].push_back(make_pair(y,ww));
		G[y].push_back(make_pair(x,ww));
	}
	dfs(1,0);
	//for(int i=1;i<n;i++) {
	//	cout<<size[i]<<" "<<ch[i][0]<<" "<<ch[i][1]<<endl;
	//}
	solve(1);
	cout<<dp[1][m]<<endl;
	return 0;
}