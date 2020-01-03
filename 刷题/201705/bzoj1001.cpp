#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define N 2100005
using namespace std;
typedef pair<int,int> pi;

struct Edge {
	int v,w;
};

vector<Edge> G[N];
int d[N];
int n,m;

int id(int x,int y,int c) 
{
	return (x*m+y)*2+c+2;
}

void add(int u,int v,int w)
{
	G[u].push_back((Edge) {v,w});
	G[v].push_back((Edge) {u,w});
}

void dijkstra(int u)
{
	priority_queue<pi,vector<pi>,greater<pi> > pq;

	memset(d,0x7f,sizeof(d));
	d[u]=0;
	pq.push(make_pair(0,u));

	while(!pq.empty()) {
		pi cur=pq.top();pq.pop();
		int u=cur.second;

		if(cur.first>d[u]) continue;
		for(unsigned int i=0;i<G[u].size();i++) {
			int v=G[u][i].v;
			if(d[u]+G[u][i].w<d[v]) {
				d[v]=d[u]+G[u][i].w;
				pq.push(make_pair(d[v],v));
			}
		}
	}  
}

int main()
{
	int w;
	scanf("%d%d",&n,&m);

	if(n<2) { //注意特判n或m=1的情况orz
		int mi=1000000;
		for(int i=0;i<m-1;i++) {
			int w;
			scanf("%d",&w);
			mi=min(mi,w);
		}
		printf("%d\n",mi);
		return 0;
	}

	if(m<2) {
		int mi=1000000;
		for(int i=0;i<n-1;i++) {
			int w;
			scanf("%d",&w);
			mi=min(mi,w);
		}
		printf("%d\n",mi);
		return 0;
	}

	for(int i=0;i<n;i++) { //横边
		for(int j=0;j<m-1;j++) {
			scanf("%d",&w);
			if(i==0) add(id(0,j,1),1,w);
			else if(i==n-1) add(id(n-2,j,0),0,w);
			else add(id(i-1,j,0),id(i,j,1),w);
		}
	}

	for(int i=0;i<n-1;i++) { //竖边
		for(int j=0;j<m;j++) {
			scanf("%d",&w);
			if(j==0) add(id(i,0,0),0,w);
			else if(j==m-1) add(id(i,m-2,1),1,w);
			else add(id(i,j-1,1),id(i,j,0),w);
		}
	}

	for(int i=0;i<n-1;i++) {
		for(int j=0;j<m-1;j++) {
			scanf("%d",&w);
			add(id(i,j,0),id(i,j,1),w);
		}
	}

	dijkstra(0);
	printf("%d\n",d[1]);

	return 0;
}