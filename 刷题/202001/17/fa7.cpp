#include <iostream>
#include <algorithm>
#include <vector>
#define N 100005
using namespace std;

typedef pair<int,int> Pii;
typedef vector<Pii>::iterator Iter;

int dfn[N],siz[N],fa[N],top[N],depth[N];
int target[N];
vector<Pii> graph[N];
int bit[2 * N];
int nn;

int qur(int idx)
{
	int ans = 0;
	while(idx) {
		ans += bit[idx];
		idx -= idx & -idx;
	}
	return ans;
}

void alt(int idx,int v)
{
	while(idx <= nn) {
		bit[idx] += v;
		idx += idx & -idx;
	}
}

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

void dfs2(int u,int uid = 0)
{
	static int cnt = 0;
	int nxt = -1,nxtid = -1,mxsiz = 0;
	dfn[u] = ++cnt;
	target[uid] = u;
	for(Iter it = graph[u].begin();it != graph[u].end();++it) {
		int v = it->first,vid = it->second;
		if(v != fa[u] && siz[v] > mxsiz) {
			nxt = v;
			nxtid = vid;
			mxsiz = siz[v];
		}
	}
	if(mxsiz) {
		top[nxt] = top[u];
		dfs2(nxt,nxtid);
		for(Iter it = graph[u].begin();it != graph[u].end();++it) {
			int v = it->first,vid = it->second;
			if(v != fa[u] && v != nxt) {
				top[v] = v;
				dfs2(v,vid);
			}
		}
	}
}

void lca(int u,int v)
{
	while(top[u] != top[v]) {
		if(depth[top[u]] < depth[top[v]]) //top!!!
			swap(u,v);
		alt(dfn[top[u]],1);
		alt(dfn[u] + 1,-1);
		u = fa[top[u]];
	}
	if(depth[u] < depth[v])
		swap(u,v);
	//do something from u to v...
	alt(dfn[v] + 1,1);
	alt(dfn[u] + 1,-1);
}

int main()
{
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for(int i = 1;i < n;i++) {
		int u,v; cin >> u >> v;
		graph[u].push_back(make_pair(v,i));
		graph[v].push_back(make_pair(u,i));
	}
	fa[1] = 1;
	top[1] = 1;
	depth[1] = 0;
	dfs1(1);
	dfs2(1);

	for(nn = 1;nn <= n;nn <<= 1);

	int m; cin >> m;
	while(m--) {
		int u,v; cin >> u >> v;
		lca(u,v);
	}

	for(int i = 1;i < n;i++) {
		cout << qur(dfn[target[i]]) << " ";
	}

	return 0;
}
