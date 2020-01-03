#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define N 1505
#define M 10005
using namespace std;

int d1[N],d2[N];
char inq[N],mark[N];
int dp[N][N];

vector<int> G[N],w[N];

void spfa(int *d,int st)
{
	queue<int> q;
	memset(d,0x7f,sizeof(int)*N);
	d[st]=0;
	inq[st]=1;
	q.push(st);

	while(!q.empty()) {
		int u=q.front();q.pop();
		inq[u]=0;
		for(unsigned int i=0;i<G[u].size();i++) {
			int v=G[u][i];
			if(d[u]+w[u][i]<d[v]) {
				d[v]=d[u]+w[u][i];
				if(!inq[v]) {
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
}

int dfs(int u1,int u2)
{
	if(dp[u1][u2]) return dp[u1][u2];
	for(unsigned int i=0;i<G[u1].size();i++) {
		int v=G[u1][i];

		if(d1[u1]+w[u1][i]!=d1[v]) continue;
		dp[u1][u2]=max(dp[u1][u2],dfs(v,u2));
	}
	for(unsigned int i=0;i<G[u2].size();i++) {
		int v=G[u2][i];

		if(d2[u2]+w[u2][i]!=d2[v]) continue;
		dp[u1][u2]=max(dp[u1][u2],dfs(u1,v));
	}
	if(u1==u2) {
		for(unsigned int i=0;i<G[u1].size();i++) {
			int v=G[u1][i];

			if(d2[u1]+w[u1][i]!=d2[v]||d1[u1]+w[u1][i]!=d1[v]) continue;
			dp[u1][u2]=max(dp[u1][u2],dfs(v,v)+1);
		}
	}

	return dp[u1][u2]?dp[u1][u2]:-1000005;
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m,u1,v1,u2,v2;
	cin>>n>>m>>u1>>v1>>u2>>v2;
	for(int i=0,u,v,ww;i<m;i++) {
		cin>>u>>v>>ww;
		G[u].push_back(v);
		G[v].push_back(u);
		w[u].push_back(ww);
		w[v].push_back(ww);
	}

	spfa(d1,u1);
	spfa(d2,u2);

	dp[v1][v2]=1;

	cout<<dfs(u1,u2)-1<<endl;
	return 0;
}