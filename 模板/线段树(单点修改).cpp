#include<bits/stdc++.h>
#define N 23333
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
		tree[p].val = tree[(p << 1) + 1].val + tree[(p << 1) + 2].val;
	}
}

void alter(int pos,int v,int p)
{
	if(pos > tree[p].r || pos < tree[p].l)
		return; 
	tree[p].val += v;
	if(tree[p].l == tree[p].r)
		return;
	alter(pos,v,(p << 1) + 1);
	alter(pos,v,(p << 1) + 2);
}

long long query(int l,int r,int p)
{
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
			cin >> l >> v;
			alter(l,v,0);
		}
	}
	return 0;
}
