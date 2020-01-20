#include <iostream>
#include <algorithm>
#include <vector>
#define N 10005
using namespace std;
typedef pair<int,int> Pii;
typedef vector<Pii>::iterator Iter;

int dfn[N],siz[N],fa[N],top[N],depth[N];
vector<Pii> graph[N];
int re[N],root[N];

void dfs1(int u)
{
	siz[u] = 1;
	for(Iter it = graph[u].begin();it != graph[u].end();++it) {
		int v = it->first;
		if(v == fa[u])
			continue;
		fa[v] = u;
		depth[v] = depth[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
	}
}

int cnt;
void dfs2(int u,int w = 0)
{
	int nxt = -1,nxtw = -1,mxsiz = 0;
	dfn[u] = ++cnt;
	re[dfn[u]] = w;
	for(Iter it = graph[u].begin();it != graph[u].end();++it) {
		int v = it->first,ww = it->second;
		if(v != fa[u] && siz[v] > mxsiz) {
			nxt = v;
			nxtw = ww;
			mxsiz = siz[v];
		}
	}
	if(mxsiz) {
		top[nxt] = top[u];
		dfs2(nxt,nxtw);
		for(Iter it = graph[u].begin();it != graph[u].end();++it) {
			int v = it->first,ww = it -> second;
			if(v != fa[u] && v != nxt) {
				top[v] = v;
				dfs2(v,ww);
			}
		}
	}
}

int lca(int u,int v)
{
	int ans = 0;
	while(top[u] != top[v]) {
		if(depth[top[u]] < depth[top[v]])
			swap(u,v);
		ans += re[dfn[u]] - re[dfn[top[u]] - 1];
		u = fa[top[u]];
	}
	if(depth[u] < depth[v])
		swap(u,v);
	return ans + re[dfn[u]] - re[dfn[v]];
}

int rt(int u)
{
	return (root[u] == u) ? u : (root[u] = rt(root[u]));
}

void merge(int u,int v)
{
	if(rt(u) != rt(v))
		root[root[u]] = root[v];
}

int main()
{
	ios::sync_with_stdio(false);
	while(1) {
		int n,m,q; cin >> n >> m >> q;
		if(cin.eof())
			return 0;
		cnt = 0;
		for(int i = 1;i <= n;i++) {
			root[i] = i;
			graph[i].clear();
		}

		for(int i = 0;i < m;i++) {
			int u,v,w; cin >> u >> v >> w;
			graph[u].push_back(make_pair(v,w));
			graph[v].push_back(make_pair(u,w));
			merge(u,v);
		}
		for(int i = 1;i <= n;i++) {
			if(root[i] == i) {
				fa[i] = i;
				top[i] = i;
				depth[i] = 0;
				dfs1(i);
				dfs2(i);
			}
		}
		for(int i = 2;i <= n;i++) {
			re[i] += re[i - 1];
		}
		while(q--) {
			int u,v; cin >> u >> v;
			if(rt(u) != rt(v)) {
				cout << "Not connected" << endl;
				continue;
			}
			cout << lca(u,v) << endl;
		}
	}
}