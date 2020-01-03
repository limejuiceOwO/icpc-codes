//NOIP2010 关押罪犯 排序+并查集判断是否二分图
#include <iostream>
#include <algorithm>
#define N 20005
#define M 100005
using namespace std;

struct Edge {
	int u,v,w;
	bool operator <(const Edge &rhs) const {
		return w>rhs.w;
	}
} edge[M];

int fa[N],dis[N];
int n,m;

int rt(int u)
{
	if(fa[u]==u) return u;
	else {
		int root=rt(fa[u]);
		dis[u]^=dis[fa[u]];
		return fa[u]=root;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i,dis[i]=0;
	for(int i=0;i<m;i++) {
		cin>>edge[i].u>>edge[i].v>>edge[i].w;
	}
	sort(edge,edge+m);
	int i;
	for(i=0;i<m;i++) {
		Edge &e=edge[i];
		if(rt(e.u)==rt(e.v)) {
			if(dis[e.u]^dis[e.v]^1) {
				break;
			}
		} else {
			dis[fa[e.v]]=dis[e.v]^dis[e.u]^1;
			fa[fa[e.v]]=fa[e.u];
		}
	}
	if(i==m) cout<<"0"<<endl;
	else cout<<edge[i].w<<endl;
	return 0;
}