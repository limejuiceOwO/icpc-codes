#include <iostream>
#include <algorithm>
#include <vector>
#define N 50005
using namespace std;

struct Seg {
	int l,r;
	int val;
} tree[16 * N];

int dfn[N],siz[N],fa[N];
vector<int> graph[N];

void build(int l,int r,int p)
{
	tree[p].l = l;
	tree[p].r = r;
	if(l < r) {
		int mid = l + ((r - l) >> 1);
		build(l,mid,(p << 1) + 1);
		build(mid + 1,r,(p << 1) + 2);
	}
	tree[p].val = -1;
}

void eval(int p)
{
	int &lz = tree[p].val;
	if(lz != -1 && tree[p].l < tree[p].r) {
		tree[(p << 1) + 1].val = lz;
		tree[(p << 1) + 2].val = lz;
		lz = -1;
	}
}

void alter(int l,int r,int v,int p)
{
	if(l > tree[p].r || r < tree[p].l) {
		eval(p);
		return;
	} else if(l <= tree[p].l && r >= tree[p].r) {
		tree[p].val = v;
		eval(p);
	} else {
		eval(p);
		alter(l,r,v,(p << 1) + 1);
		alter(l,r,v,(p << 1) + 2);
	}
}

int query(int pos,int p)
{
	eval(p);
	if(pos == tree[p].l && pos == tree[p].r) {
		return tree[p].val;
	} else if(pos > tree[p].r || pos < tree[p].l) {
		return 0;
	} else {
		return query(pos,(p << 1) + 1) + query(pos,(p << 1) + 2);
	}
}

void dfs(int u)
{
	static int id = 0;
	if(!fa[u])
		id = 0;
	dfn[u] = ++id;
	siz[u] = 1;
	for(size_t i = 0;i < graph[u].size();i++) {
		int v = graph[u][i];
		if(v == fa[u])
			continue;
		dfs(v);
		siz[u] += siz[v];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int t; cin >> t;
	for(int i = 1;i <= t;i++) {
		cout << "Case #" << i << ":" << endl;
		int n; cin >> n;
		for(int i = 1;i <= n;i++) {
			graph[i].clear();
			fa[i] = 0;
		}
		for(int i = 1;i < n;i++) {
			int u,v; cin >> u >> v;
			graph[v].push_back(u);
			fa[u] = v;
		}
		for(int i = 1;i <= n;i++) {
			if(!fa[i]) {
				dfs(i);
				break;
			}
		}
		build(1,n,0);
		int m; cin >> m;
		while(m--) {
			string cmd;
			int x,y;
			cin >> cmd;
			if(cmd[0] == 'C') {
				cin >> x;
				cout << query(dfn[x],0) << endl;
			} else if(cmd[0] == 'T') {
				cin >> x >> y;
				alter(dfn[x],dfn[x] + siz[x] - 1,y,0);
			}
		}
	}
	return 0;
}