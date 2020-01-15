#include<bits/stdc++.h>
#define N 4000000
#define INF 2e9
using namespace std;

struct Seg {
	int l,r;
	long long val;
} tree[N];

void build(int l,int r,int p)
{
	tree[p].l = l;
	tree[p].r = r;
	if(l == r) {
		cin >> tree[p].val;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l,mid,(p << 1) + 1);
		build(mid + 1,r,(p << 1) + 2);
		tree[p].val = max(tree[(p << 1) + 1].val, tree[(p << 1) + 2].val);
	}
}

void alter(int pos,int v,int p)
{
	if(pos > tree[p].r || pos < tree[p].l)
		return; 
	if(tree[p].l == tree[p].r) {
		tree[p].val = v;
		return;
	}
	alter(pos,v,(p << 1) + 1);
	alter(pos,v,(p << 1) + 2);
	tree[p].val = max(tree[(p << 1) + 1].val, tree[(p << 1) + 2].val);
}

long long query(int l,int r,int p)
{
	if(l <= tree[p].l && r >= tree[p].r) {
		return tree[p].val;
	} else if(l > tree[p].r || r < tree[p].l) {
		return -INF;
	} else {
		return max(query(l,r,(p << 1) + 1),query(l,r,(p << 1) + 2));
	}
}

int main()
{
	ios::sync_with_stdio(false);
	while(1) {
		int n,m;
		cin >> n >> m;
		if(cin.eof())
			return 0;
		build(0,n - 1,0);
		while(m--) {
			string cmd;
			int l,r,v;
			cin >> cmd;
			if(cmd[0] == 'Q') {
				cin >> l >> r;
				cout << query(l - 1,r - 1,0) << endl;
			} else if(cmd[0] == 'U') {
				cin >> l >> v;
				alter(l - 1,v,0);
			}
		}
	}
}
