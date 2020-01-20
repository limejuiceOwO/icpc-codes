#include <iostream>
#include <algorithm>
#include <vector>
#define N 40005
using namespace std;
typedef pair<int,int> Pii;
typedef vector<Pii>::iterator Iter;

int dfn[N],siz[N],fa[N],top[N],depth[N];
vector<Pii> graph[N];
int arr[N];

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

int cnt = 0;
void dfs2(int u,int w = 0)
{
	int nxt = -1,nxtw = -1,mxsiz = 0;
	dfn[u] = ++cnt;
	arr[dfn[u]] = w;
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
		ans += arr[dfn[u]] - arr[dfn[top[u]] - 1];
		u = fa[top[u]];
	}
	if(depth[u] < depth[v])
		swap(u,v);
	return ans + arr[dfn[u]] - arr[dfn[v]];
}

int main()
{
	ios::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) {
		int n,m; cin >> n >> m;
		for(int i = 1;i <= n;i++)
			graph[i].clear();
		for(int i = 1;i < n;i++) {
			int u,v,w; cin >> u >> v >> w;
			graph[u].push_back(make_pair(v,w));
			graph[v].push_back(make_pair(u,w));
		}
		fa[1] = 1;
		top[1] = 1;
		depth[1] = 0;
		cnt = 0;
		dfs1(1);
		dfs2(1);

		for(int i = 2;i <= n;i++) {
			arr[i] += arr[i - 1];
		}

		while(m--) {
			int u,v; cin >> u >> v;
			cout << lca(u,v) << endl;
		}
	}
	return 0;
}