#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 205
#define M 205
#define INF 100000005
using namespace std;

struct Edge {
	int v,flow,mxflow,rev;
} edge[M];
int ecnt=0;

vector<int> G[N];
char vis[N];

int dfs(int u,int t,int e)
{
	if(u==t) return e;
	for(unsigned int i=0;i<G[u].size();i++) {
		Edge &cur=edge[G[u][i]];
		int v=cur.v;
		if(vis[v]||cur.flow==cur.mxflow) continue;
		vis[v]=1;
		int ret=dfs(v,t,min(e,cur.mxflow-cur.flow));
		if(ret) {
			cur.flow+=ret;
			edge[cur.rev].flow-=ret;
			return ret;
		}
	}
	return 0;
}

int karp(int s,int t)
{
	int ans=0;
	int r;
	while(1) {
		//cout<<ans<<endl;
		memset(vis,0,sizeof(vis));
		vis[s]=1;
		if(!(r=dfs(s,t,INF))) break;
		ans+=r;
	}
	return ans;
}

int main()
{
	while(1) {
		int n,m;
		cin>>m>>n;
		if(cin.eof()) break;
		ecnt=0;
		for(int i=1;i<=n;i++) G[i].clear();
		for(int i=0;i<m;i++) {
			int u,v,flow;
			cin>>u>>v>>flow;
			edge[ecnt]=(Edge){v,0,flow,ecnt+1};
			edge[ecnt+1]=(Edge){u,flow,flow,ecnt};
			G[u].push_back(ecnt++);
			G[v].push_back(ecnt++);
		}
		cout<<karp(1,n)<<endl;
	}
	return 0;
}