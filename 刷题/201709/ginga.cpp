#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define N 100005
using namespace std;
 
struct Edge {
	int v,w;
};
struct Qur {
	int t,a,b;
}qur[N];
int qcnt;
 
vector<Edge> G[N];
int fa[N],d[N];
char inq[N];
const int dw[]={0,0,1,0,1,0};
 
int findrt(int u)
{
	return fa[u]==u ? u : fa[u]=findrt(fa[u]);
}
 
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		fa[i]=i;
 
	for(int i=0;i<m;i++) {
		Qur &q=qur[qcnt];
		cin>>q.t>>q.a>>q.b;
		if(q.t==1) {
			int r1=findrt(q.a),r2=findrt(q.b);
			if(r1==r2) continue;
			fa[r1]=r2;
		} else {
			qcnt++;
		}
	} //1a=b 2a<b 3a>=b 4a>b 5a<=b
 
	for(int i=0;i<qcnt;i++) {
		Qur &q=qur[i];
		if(q.t==3||q.t==4) swap(qur[i].a,qur[i].b);
		G[findrt(q.a)].push_back((Edge) {findrt(q.b),dw[q.t]});
	}
 
	queue<int> que;
	fill(d,d+n+5,1);
	for(int i=1;i<=n;i++) {
		if(fa[i]==i) {
			que.push(i);
			inq[i]=1;
		}
	}
 
	while(!que.empty()) {
		int u=que.front();que.pop();
		inq[u]=0;
		for(unsigned int i=0;i<G[u].size();i++) {
			int v=findrt(G[u][i].v);
			if(d[u]+G[u][i].w>d[v]) {
				d[v]=d[u]+G[u][i].w;
				if(!inq[v]) {
					que.push(v);
					inq[v]=1;
				}
			}
		}
	}
 
	int ans=0;
	for(int i=1;i<=n;i++) {
		ans+=d[findrt(i)];
	}
	cout<<ans<<endl;
	return 0;
}