#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define N 100005
using namespace std;

typedef pair<int,int> pii;
vector<pii> G[N];
char vis[N];
int n;

long long prim(int st)
{
	long long sum=0;
	int cnt=0;
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	pq.push(make_pair(0,st));
	memset(vis,0,sizeof(vis));
	while(!pq.empty()) {
		pii e=pq.top();pq.pop();
		int w=e.first,u=e.second;
		if(vis[u]) continue;
		vis[u]=1;
		sum+=w;
		if(++cnt>=n) return sum;
		for(unsigned int i=0;i<G[u].size();i++) {
			int v=G[u][i].first,ww=G[u][i].second;
			if(!vis[v]) pq.push(make_pair(ww,v));
		}
	}
	return -1;
}

int main()
{
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m;
	for(int i=0,u,v,w;i<m;i++) {
		cin>>u>>v>>w;
		G[u].push_back(make_pair(v,w));
		G[v].push_back(make_pair(u,w));
	}
	cout<<prim(1)<<endl;
	return 0;
}