#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#define N 105
#define M 25
#define INF 1000005
using namespace std;

struct Constrain {
	int st,ed;
};

int G[M][M];
vector<Constrain> ct[M];
int dp[N],cost[N][N];
int dis[M];
int n,m,k;

bool check(int u,int st,int ed)
{
	for(unsigned int i=0;i<ct[u].size();i++) {
		if((ed>=ct[u][i].st&&ed<=ct[u][i].ed)||
			(st>=ct[u][i].st&&st<=ct[u][i].ed)||
			(st<=ct[u][i].st&&ed>=ct[u][i].ed))
				return false;
	}
	return true;
}

int dijkstra(int st,int ed)
{
	priority_queue<pair<int,int> > pq;
	memset(dis,0x7f,sizeof(dis));
	dis[1]=0;
	pq.push(make_pair(0,1));
	while(!pq.empty()) {
		pair<int,int> p=pq.top();pq.pop();
		int u=p.second;
		if(p.first>dis[u]) continue;
		for(int v=1;v<=m;v++) {
			if(!G[u][v]||!check(v,st,ed)) continue;
			if(dis[u]+G[u][v]<dis[v]) {
				dis[v]=dis[u]+G[u][v];
				pq.push(make_pair(dis[v],v));
			}
		}
	}
	return min(dis[m],INF);
}

int main()
{
	ios::sync_with_stdio(false);
	int e,d;
	cin>>n>>m>>k>>e;
	for(int i=0;i<e;i++) {
		int u,v,c;
		cin>>u>>v>>c;
		G[u][v]=G[v][u]=c;
	}
	cin>>d;
	for(int i=0;i<d;i++) {
		int u,st,ed;
		cin>>u>>st>>ed;
		ct[u].push_back((Constrain){st,ed});
	}
	for(int i=1;i<=n;i++) {
		for(int j=i;j<=n;j++) {
			cost[i][j]=dijkstra(i,j)*(j-i+1);
		}
	}
	for(int i=1;i<=n;i++) {
		dp[i]=cost[1][i];
		for(int j=1;j<i;j++) {
			dp[i]=min(dp[i],dp[j]+cost[j+1][i]+k);
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}