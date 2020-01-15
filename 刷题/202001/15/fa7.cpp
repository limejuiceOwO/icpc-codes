#include <bits/stdc++.h>
#define N 200005
using namespace std;

struct Seg {
	int l,r;
	int val;
	bool lazy;
} tree[N * 18];

int orig[N];
int dfn[N],siz[N];
vector<int> graph[N];

void build(int l,int r,int p)
{
	tree[p].l = l;
	tree[p].r = r;
	if(l == r) {
		tree[p].val = orig[l];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l,mid,(p << 1) + 1);
		build(mid + 1,r,(p << 1) + 2);
		tree[p].val = tree[(p << 1) + 1].val + tree[(p << 1) + 2].val;
	}
}

void eval(int p)
{
	bool &lz = tree[p].lazy;
	if(lz) {
		if(tree[p].l < tree[p].r) {
			tree[(p << 1) + 1].lazy ^= 1;
			tree[(p << 1) + 2].lazy ^= 1;
		}
		tree[p].val = tree[p].r - tree[p].l + 1 - tree[p].val;
		lz = false;
	}
}

void alter(int l,int r,int p)
{
	if(l > tree[p].r || r < tree[p].l) {
		eval(p);
		return;
	} else if(l <= tree[p].l && r >= tree[p].r) {
		tree[p].lazy ^= 1;
		eval(p);
	} else {
		eval(p);
		alter(l,r,(p << 1) + 1);
		alter(l,r,(p << 1) + 2);
		tree[p].val = tree[(p << 1) + 1].val + tree[(p << 1) + 2].val;
	}
}

long long query(int l,int r,int p)
{
	eval(p);
	if(l <= tree[p].l && r >= tree[p].r) {
		return tree[p].val;
	} else if(l > tree[p].r || r < tree[p].l) {
		return 0;
	} else {
		return query(l,r,(p << 1) + 1) + query(l,r,(p << 1) + 2);
	}
}

void dfs(int u,int fa = 0)
{
	static int id = 0;
	dfn[u] = ++id;
	siz[u] = 1;
	for(size_t i = 0;i < graph[u].size();i++) {
		int v = graph[u][i];
		if(v == fa)
			continue;
		dfs(v,u);
		siz[u] += siz[v];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int n; cin >> n;
	for(int i = 2;i <= n;i++) {
		int fa; cin >> fa;
		graph[fa].push_back(i);
	}
	dfs(1);
	for(int i = 1;i <= n;i++) {
		cin >> orig[dfn[i]];
	}
	build(1,n,0);
	int m; cin >> m;
	while(m--) {
		string cmd;
		int p;
		cin >> cmd >> p;
		if(cmd[0] == 'g') {
			cout << query(dfn[p],dfn[p] + siz[p] - 1,0) << endl;
		} else if(cmd[0] == 'p') {
			alter(dfn[p],dfn[p] + siz[p] - 1,0);
		}
	}
	return 0;
}