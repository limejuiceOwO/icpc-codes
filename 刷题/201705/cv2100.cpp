#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define N 60005
#define M 400005
#define INF 100000005
using namespace std;

struct Edge {
	int v,flow,max_flow;
} edge[2*M];

vector<int> G[N];
int n,m,cnt=0;
int lvl[N];
char vis[N];

inline int point(int x,int y) //x列y行
{
	return x*m+y;
}

bool bfs(int st,int ed)
{
	queue<int> q;
	memset(lvl,0,sizeof(lvl));
	q.push(st);
	lvl[st]=1;
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(unsigned int i=0;i<G[u].size();i++) {
			int p=G[u][i],v=edge[p].v;
			if(lvl[v]||edge[p].flow>=edge[p].max_flow) continue;
			lvl[v]=lvl[u]+1;
			if(v==ed) return true;
			q.push(v);
		}
	}
	return false;
}

int dfs(int u,int ed,int e=INF)
{
	if(u==ed) return e;
	for(unsigned int i=0;i<G[u].size();i++) {
		int p=G[u][i],v=edge[p].v;
		if(vis[v]||lvl[v]<=lvl[u]||edge[p].flow>=edge[p].max_flow) continue;
		vis[v]=1;
		int ret=dfs(v,ed,min(e,edge[p].max_flow-edge[p].flow));
		if(ret) {
			edge[p].flow+=ret;
			edge[p^1].flow-=ret;
			return ret;
		}
	}
	return 0;
}

int max_flow(int st,int ed)
{
	int ans=0,cur;
	while(1) {
		if(!bfs(st,ed)) break;
		while(1) {
			memset(vis,0,sizeof(vis));
			vis[st]=1;
			if(!(cur=dfs(st,ed))) break;
			ans+=cur;
			if(ans>=INF) break;
		}
	}
	return ans;
}

void add(int u,int v,int f)
{
	edge[cnt]=(Edge){v,0,f};
	edge[cnt^1]=(Edge){u,f,f};
	G[u].push_back(cnt++);
	G[v].push_back(cnt++);
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m-1;j++) {
			int f,u=point(i,j),v=point(i,j+1);
			cin>>f;
			add(u,v,f);
			add(v,u,f);
		}
	}
	for(int j=0;j<m;j++) {
		for(int i=0;i<n-1;i++) {
			int f,u=point(i,j),v=point(i+1,j);
			cin>>f;
			add(u,v,f);
			add(v,u,f);
		}
	}
	cout<<max_flow(0,point(n-1,m-1))/2<<endl;
	//cout<<max_flow(0,point(n-1,m-1))<<endl;
	return 0;
}