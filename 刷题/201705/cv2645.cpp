#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define N 1005
#define INF 10000005
using namespace std;

vector<int> G[N],cost[N];
int d[N],cnt[N];
char inque[N];
int n;

bool spfa(int st)
{
	queue<int> q;
	memset(d,0x7f,sizeof(d));
	memset(cnt,0,sizeof(cnt));
	memset(inque,0,sizeof(inque));
	q.push(st);
	d[st]=0;
	//inque[st]=1;
	while(!q.empty()) {
		int u=q.front();q.pop();
		inque[u]=0;
		for(unsigned int i=0;i<G[u].size();i++) {
			int v=G[u][i],c=cost[u][i];
			if(d[u]+c<d[v]) {
				d[v]=d[u]+c;
				if(++cnt[v]>n) return false;
				if(!inque[v]) {
					inque[v]=1;
					q.push(v);
				}
			}
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	int m;
	while(1) {
		cin>>n>>m;
		if(n==0&&m==0) break;
		for(int i=1;i<=n;i++) {
			G[i].clear();
			cost[i].clear();
		}
		for(int i=0;i<m;i++) {
			int u,v,c1,c2;
			cin>>u>>v>>c1>>c2;
			G[u].push_back(v);
			cost[u].push_back(c1);
			G[v].push_back(u);
			cost[v].push_back(c2);
		}
		if(!spfa(1)||d[n]>=INF) {
			cout<<"No such path"<<endl;
		} else {
			cout<<d[n]<<endl;
		}
	}
	return 0;
}