#include <iostream>
#include <algorithm>
#define N 23333
using namespace std;

struct Seg {
	int l,r;
	long long val,lazy;
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
		tree[p].val = tree[(p << 1) + 1].val + tree[(p << 1) + 2].val;
	}
}

void eval(int p)
{
	long long &lz = tree[p].lazy;
	if(lz) {
		if(tree[p].l < tree[p].r) {
			tree[(p << 1) + 1].lazy += lz;
			tree[(p << 1) + 2].lazy += lz;
		}
		tree[p].val += lz * (tree[p].r - tree[p].l + 1);
		lz = 0;
	}
}

void alter(int l,int r,int v,int p)
{
	if(l > tree[p].r || r < tree[p].l) {
		eval(p);
		return;
	} else if(l <= tree[p].l && r >= tree[p].r) {
		tree[p].lazy += v;
		eval(p);
	} else {
		eval(p);
		alter(l,r,v,(p << 1) + 1);
		alter(l,r,v,(p << 1) + 2);
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

int main()
{
	int n;
	cin >> n;
	build(0,n - 1,0);
	while(1) {
		int cmd,l,r,v;
		cin >> cmd;
		if(cmd == 1) {
			cin >> l >> r;
			cout << query(l,r,0) << endl;
		} else {
			cin >> l >> r >> v;
			alter(l,r,v,0);
		}
	}
	return 0;
}
