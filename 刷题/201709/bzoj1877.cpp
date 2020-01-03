#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define M 20005
#define N 205
#define INF 100000005
using namespace std;

struct Edge {
	int v,cost,flow,mxflow;
} edge[2*M+2*N];
int ecnt;
vector<int> G[2*N];
long long d[2*N];
int pre[2*N],pree[2*N];
char inque[2*N];

void add(int u,int v,int flow,int cost)
{
	edge[ecnt]=(Edge){v,cost,0,flow};
	edge[ecnt+1]=(Edge){u,-cost,flow,flow};
	G[u].push_back(ecnt++);
	G[v].push_back(ecnt++);
}

bool spfa(int from,int to)
{
	queue<int> que;
	memset(d,0x7f,sizeof(d));
	memset(inque,0,sizeof(inque));
	d[from]=0;
	que.push(from);
	inque[from]=1;

	while(!que.empty()) {
		int u=que.front();que.pop();
		inque[u]=0;
		for(unsigned int i=0;i<G[u].size();i++) {
			Edge &cur=edge[G[u][i]];
			int v=cur.v;
			if(cur.flow<cur.mxflow&&d[u]+cur.cost<d[v]) {
				d[v]=d[u]+cur.cost;
				pre[v]=u;
				pree[v]=G[u][i];
				if(!inque[v]) {
					inque[v]=1;
					que.push(v);
				}
			}
		}
	}

	if(d[to]>=INF) return false;
	return true;
}

int min_cost_max_flow(int from,int to,long long &cost)
{
	cost=0;
	int f=0;
	while(spfa(from,to)) {
		int p=to,df=INF;
		while(p!=from) {
			df=min(df,edge[pree[p]].mxflow-edge[pree[p]].flow);
			p=pre[p];
		}
		
		p=to;
		while(p!=from) {
			edge[pree[p]].flow+=df;
			edge[pree[p]^1].flow-=df;
			p=pre[p];
		}

		cost+=d[to]*df;
		f+=df;
	}

	return f;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);

	//add(1,n+1,INF,0);
	//add(n,2*n,INF,0);
	for(int i=2;i<n;i++) {
		add(i,i+n,1,0);
	}

	for(int i=0,u,v,w;i<m;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(u+n,v,1,w); //容量为INF会发生什么？
	}

	long long cost;
	printf("%d ",min_cost_max_flow(n+1,n,cost));
	printf("%lld\n",cost);
	return 0;
}