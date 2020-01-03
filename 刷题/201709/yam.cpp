#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 100005
#define NN 262147
using namespace std;

struct SEdge {
	int v,id;
};
vector<int> G[N];
vector<SEdge> G2[N];
int bit[NN],dfn[N],cnt[N],mark[2*N];//m<=200000
int n;

void alt(int pos,int x)
{
	if(x==0) cout<<"FaQ"<<endl;
	while(pos<=n) {
		bit[pos]+=x;
		pos+=(pos&-pos);
	}
}

int qur(int pos)
{
	int ans=0;
	while(pos) {
		ans+=bit[pos];
		pos-=(pos&-pos);
	}

	return ans;
}

void dfs1(int u)
{
	static int cdfn;
	dfn[u]=++cdfn;
	for(unsigned int i=0;i<G2[u].size();i++) {
		SEdge &s=G2[u][i];
		if(mark[s.id]) {
			alt(dfn[s.v],-1);
			alt(dfn[u],1);
		} else {
			mark[s.id]++;
		}
	}
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(dfn[v]) continue;
		dfs1(v);
	}
	cnt[u]+=qur(cdfn)-qur(dfn[u]-1);
}

void dfs2(int u)
{
	static int cdfn;
	++cdfn;
	for(unsigned int i=0;i<G2[u].size();i++) {
		SEdge &s=G2[u][i];
		alt(dfn[s.v],-1);
		alt(dfn[u],1);
	}
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(dfn[v]<dfn[u]) continue;
		dfs2(v);
	}
	cnt[u]+=qur(cdfn)-qur(dfn[u]-1);
}

int main()
{
	ios::sync_with_stdio(false);

	int k;
	cin>>n>>k;
	for(int i=0;i<n-1;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=0;i<k;i++) {
		int u,v;
		cin>>u>>v;
		G2[u].push_back((SEdge){v,i});
		G2[v].push_back((SEdge){u,i});
	}

	dfs1(1);
	memset(bit,0,sizeof(bit));
	dfs2(1);

	int ans=0;
	for(int i=2;i<=n;i++) {
		ans+=cnt[i]>1 ? 0 : (cnt[i]==1 ? 1 : k);
	}

	cout<<ans<<endl;
	return 0;
}