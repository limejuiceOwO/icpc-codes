//最优布线问题 最小生成树
#include <iostream>
#include <algorithm>
#define N 100005
#define M 100005
using namespace std;

struct Edge {
	int u,v,w;
	bool operator <(const Edge &rhs) const {
		return w<rhs.w;
	}
} edges[M];
int fa[N];

int root(int u)
{
	return fa[u]==u?u:(fa[u]=root(fa[u]));
}

int main() 
{
	ios::sync_with_stdio(false);
	int n,m;
	long long sum=0;
	cin>>n>>m;
	for(int i=0;i<=n;i++) fa[i]=i;
	for(int i=0;i<m;i++) {
		Edge &n=edges[i];
		cin>>n.u>>n.v>>n.w;
	}
	sort(edges,edges+m);
	for(int i=0;i<m;i++) {
		Edge &n=edges[i];
		if(root(n.u)==root(n.v)) continue;
		sum+=n.w;
		fa[root(n.u)]=root(n.v);
	}
	cout<<sum<<endl;
	return 0;
}
