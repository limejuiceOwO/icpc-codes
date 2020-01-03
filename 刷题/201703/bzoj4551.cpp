//[Tjoi2016&Heoi2016]树
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#define N 100005
#define M 100005
using namespace std;

vector<int> G[N];
char cmds[M];
int root[N],fa[N],cnt[N],cmdu[M],ans[M];
int n,top=0;

int find(int u)
{
	return (root[u]==u)?u:(root[u]=find(root[u]));
}

void dfs(int u)
{
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		fa[v]=u;
		root[v]=cnt[v]?v:root[u];
		dfs(v);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++) {
		cin>>u>>v;
		G[u].push_back(v);
	}
	cnt[1]=root[1]=fa[1]=1;
	for(int i=0,u;i<m;i++) {
		char cmd[3];
		cin>>cmd>>u;
		if(cmd[0]=='C') {
			cnt[u]++;
		}
		cmds[i]=cmd[0];
		cmdu[i]=u;
	}
	dfs(1);
	for(int i=m-1;i>=0;i--) {
		if(cmds[i]=='C') {
			if(!(--cnt[cmdu[i]])) {
				root[cmdu[i]]=fa[cmdu[i]];
			}
		} else {
			ans[top++]=find(cmdu[i]);
		}
	}
	while(top) cout<<ans[--top]<<endl;
	return 0;
}