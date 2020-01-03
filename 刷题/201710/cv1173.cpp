#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define N 100005
using namespace std;

vector<int> G[N],Gr[N];
int w[N];
int d1[N],d2[N];
char inq[N];

void spfa(vector<int> G[],int *d,int st,int type)
{
	memset(inq,0,sizeof(inq));
	memset(d,type ? 0x7f : 0x80,sizeof(int)*N);
	d[st]=w[st];
	inq[st]=1;

	queue<int> que;
	que.push(st);
	while(!que.empty()) {
		int u=que.front();que.pop();
		inq[u]=0;
		for(unsigned int i=0;i<G[u].size();i++) {
			int v=G[u][i];
			int nw=type ? min(d[u],w[v]) : max(d[u],w[v]);
			if(type ? nw<d[v] : nw>d[v]) {
				d[v]=nw;
				if(!inq[v]) {
					que.push(v);
					inq[v]=1;
				}
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m;

	for(int i=1;i<=n;i++) {
		cin>>w[i];
	}
	for(int i=0,u,v,z;i<m;i++) {
		cin>>u>>v>>z;
		G[u].push_back(v);
		Gr[v].push_back(u);
		if(z==2) {
			G[v].push_back(u);
			Gr[u].push_back(v);
		}
	}

	spfa(G,d1,1,1);
	spfa(Gr,d2,n,0);

	int ans=0;
	for(int i=1;i<=n;i++) {
		ans=max(ans,d2[i]-d1[i]);
	}
	cout<<ans<<endl;
	return 0;
}