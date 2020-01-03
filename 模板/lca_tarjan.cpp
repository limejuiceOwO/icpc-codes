#include <iostream>
#include <algorithm>
#include <vector>
#define N 1005
using namespace std;

int root[N],vis[N],qhead[N],qnext[N];
int qcnt=1;
struct Qur {
	int v,ans;
} qur[N];
vector<int> G[N];

int find(int u)
{
	return (root[u]==u)?u:(root[u]=find(root[u]));
}

void tarjan(int u)
{
	vis[u]=1;
	root[u]=u;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(vis[v]) continue;
		tarjan(v);
		root[v]=u;
	}
	for(int i=qhead[u];i;i=qnext[i]) {
		int v=qur[i].v;
		if(vis[v]) qur[i].ans=qur[i+1].ans=find(v);
	}
}

void ins(int u,int v)
{
	qur[qcnt].v=v;
	qnext[qcnt]=qhead[u];
	qhead[qcnt]=qcnt++;
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1,u,v;i<n;i++) {
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=0,u,v;i<m;i++) {
		cin>>u>>v;
		ins(u,v);
		ins(v,u);
	}
	tarjan(1);
	for(int i=1;i<=n;i++) {
		for(unsigned int j=0;j<ans[i].size();j++) {
			cout<<i<<" "<<qur[i][j]<<" "<<ans[i][j]<<endl;
		}
	}
	return 0;
}