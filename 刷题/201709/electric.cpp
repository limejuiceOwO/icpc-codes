#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 305
#define INF 100000005
using namespace std;

int n,m,k;
vector<int> G[N],w[N];
int dp[N][N][2],nxt[N][2],size[N];

void upd(int &a,int b)
{
	a=min(a,b);
}

void dfs(int u,int fa=0)
{
	dp[u][0][0]=dp[u][1][1]=0;
	size[u]=1;

	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u);
		size[u]+=size[v];
	}

	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		
		for(int kk=0;kk<=size[u];kk++) {
			nxt[kk][0]=nxt[kk][1]=INF; //每棵子树作为一个阶段转移，不要直接在原数组上转移
			//即dp(i,j,k,0/1):-树i考虑前j棵子树，集合1节点数为k的最优解
			for(int l=0;l<=min(kk,size[v]);l++) {
				upd(nxt[kk][1],dp[u][kk-l][1]+dp[v][l][1]+w[u][i]);
				upd(nxt[kk][1],dp[u][kk-l][1]+dp[v][l][0]);
				upd(nxt[kk][0],dp[u][kk-l][0]+dp[v][l][0]+(m==2 ? w[u][i] : 0));
				upd(nxt[kk][0],dp[u][kk-l][0]+dp[v][l][1]);
			}
		}
		memcpy(dp[u],nxt,sizeof(nxt));
	}
}

int main()
{
	ios::sync_with_stdio(false);

	cin>>n>>m>>k;

	if(n<m-1+k) {
		cout<<"-1"<<endl;
		return 0;
	}

	for(int i=0,u,v,ww;i<n-1;i++) {
		cin>>u>>v>>ww;
		G[u].push_back(v);
		G[v].push_back(u);
		w[u].push_back(ww);
		w[v].push_back(ww);
	}

	for(int i=0;i<=n;i++) {
		for(int j=0;j<=n;j++) {
			dp[i][j][0]=dp[i][j][1]=INF;
		}
	}

	dfs(1);

	if(dp[1][k][1]<INF)
		cout<<dp[1][k][1]<<endl;
	else
		cout<<"-1"<<endl;

	return 0;
}