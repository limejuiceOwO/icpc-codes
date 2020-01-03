#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#define N 1005
using namespace std;
typedef pair<int,int> pii;

struct Edge {
	int v,w;
};
vector<Edge> G[N][25];
int d[N][25],d2[N][25],src[25][N][25],fa[25][N][25];
char inq[N][25],cov[N][25];

int main()
{
	ios::sync_with_stdio(false);

	int n,m,c,t,s,e;
	cin>>n>>m>>c>>t;
	cin>>s>>e;

	for(int i=0;i<m;i++) {
		int u,v,cnt,tt,h=0;
		cin>>cnt>>u;
		cov[u][i]=1;
		for(int j=0;j<cnt-1;j++) {
			cin>>v>>tt;
			cov[v][i]=1;
			G[u][i].push_back((Edge) {v,tt-h});
			G[v][i].push_back((Edge) {u,tt-h});
			h=tt;
			u=v;
		}
	}

	queue<pii> que; 
	memset(d,0x7f,sizeof(d));
	for(int i=0;i<m;i++) {
		if(cov[s][i]) {
			d[s][i]=0;
			src[0][s][i]=s;
			que.push(make_pair(s,i));
			inq[s][i]=1;
		}
	}

	for(int change=0;change<=c;change++) {
		while(!que.empty()) {
			pii cur=que.front();que.pop();
			int u=cur.first,id=cur.second;
			inq[u][id]=0;
			for(unsigned int i=0;i<G[u][id].size();i++) {
				int v=G[u][id][i].v;
				if(d[v][id]>d[u][id]+G[u][id][i].w) {
					d[v][id]=d[u][id]+G[u][id][i].w;
					src[change][v][id]=src[change][u][id];
					if(!inq[v][id]) {
						inq[v][id]=1;
						que.push(make_pair(v,id));
					}
				}
			}
		}

		for(int i=0;i<m;i++) {
			if(d[e][i]<=t) {
				cout<<change<<endl;
				stack<pii> ans;
				while(e!=s) {
					e=src[change][e][i];
					ans.push(make_pair(e,i));
					i=fa[change][e][i];
					change--;
				}
				cout<<ans.top().second+1<<endl;
				ans.pop();
				while(!ans.empty()) {
					cout<<ans.top().first<<" "<<ans.top().second+1<<endl;
					ans.pop();
				}
				return 0;
			}
		}

		memset(d2,0x7f,sizeof(d2));
		for(int i=1;i<=n;i++) {
			for(int j=0;j<m;j++) {
				for(int k=0;k<m;k++) {
					if(j==k||d[i][k]>t||!cov[i][k]||!cov[i][j]) continue;
					if(d2[i][j]>d[i][k]) {
						d2[i][j]=d[i][k];
						fa[change+1][i][j]=k;
						src[change+1][i][j]=i;
						if(!inq[i][j]) {
							inq[i][j]=1;
							que.push(make_pair(i,j));
						}
					}
				}
			}
		}
		memcpy(d,d2,sizeof(d2));
	}

	cout<<"-1"<<endl;
	return 0;
}