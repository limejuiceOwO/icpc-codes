#include <algorithm>
#include <vector>

typedef pair<int,int> Pii;
typedef vector<Pii>::iterator Iter;

int dfn[N],siz[N],fa[N],top[N],depth[N];
vector<Pii> graph[N];
int re[N];

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

void dfs2(int u,int w = 0)
{
	static int cnt;
	if(depth[u] == 0)
		cnt = 0;
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
	while(top[u] != top[v]) {
		if(depth[top[u]] < depth[top[v]]) //top!!!
			swap(u,v);
		//do something from u to top[u]...
		u = fa[top[u]];
	}
	if(depth[u] < depth[v])
		swap(u,v);
	//do something from u to v...
	return v;
}

int main()
{
	//graph input
	fa[root] = root;
	top[root] = root;
	depth[root] = 0;
	dfs1(root);
	dfs2(root);
	//perhaps segment tree initialization with re[]...
}