#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define N 300005
using namespace std;

struct Route {
	int u,v,rev;
	Route(int _u,int _v,int _rev):u(_u),v(_v),rev(_rev){};
};

vector<Route> r[N];
vector<int> G[N],d1[N],d2[N],d3[N],d4[N];
int T[N],depth[N],fa[N],anc[N],buk1[N],buk2[2*N],ans[N];
char vis[N];

int rt(int u)
{
	return (fa[u]==u)?u:(fa[u]=rt(fa[u]));
}

void addroute(int st,int ed,int lca)
{
	d1[st].push_back(depth[st]);
	d2[anc[lca]].push_back(depth[st]);
	d3[ed].push_back(2*depth[lca]-depth[st]+N);
	d4[lca].push_back(2*depth[lca]-depth[st]+N);
}

void tarjan(int u)
{
	fa[u]=u;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==anc[u]) continue;
		anc[v]=u;
		depth[v]=depth[u]+1;//MDZZ，不小心放递归后边了...
		tarjan(v);
	}
	vis[u]=1;
	for(unsigned int i=0;i<r[u].size();i++) {
		int v=r[u][i].v;
		if(vis[v]) r[u][i].rev?addroute(v,u,rt(v)):addroute(u,v,rt(v));
	}
	fa[u]=anc[u];//u=1?
}

void dfs(int u)
{
	if(depth[u]+T[u]<N) ans[u]-=buk1[depth[u]+T[u]];
	if(depth[u]-T[u]<N&&depth[u]-T[u]+N>=0) ans[u]-=buk2[depth[u]-T[u]+N];
	for(unsigned int j=0;j<d1[u].size();j++) buk1[d1[u][j]]++;
	for(unsigned int j=0;j<d2[u].size();j++) buk1[d2[u][j]]--;
	for(unsigned int j=0;j<d3[u].size();j++) buk2[d3[u][j]]++;
	for(unsigned int j=0;j<d4[u].size();j++) buk2[d4[u][j]]--;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==anc[u]) continue;
		dfs(v);
	}
	if(depth[u]+T[u]<N) ans[u]+=buk1[depth[u]+T[u]]; //注意特判T[u]范围
	if(depth[u]-T[u]<N&&depth[u]-T[u]+N>=0) ans[u]+=buk2[depth[u]-T[u]+N];
}

int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++) cin>>T[i];
	for(int i=0;i<m;i++) {
		int u,v;
		cin>>u>>v;
		r[u].push_back(Route(u,v,0));
		if(v!=u) r[v].push_back(Route(v,u,1)); //此时depth未初始化
	}
	//depth[1]=0;anc[1]=0;
	tarjan(1);
	dfs(1);
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<endl;
	return 0;
}