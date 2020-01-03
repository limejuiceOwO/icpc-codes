//可持久化并查集+二分+启发式合并
#include <iostream>
#include <algorithm>
#define N 50005
#define NN 5000005
using namespace std;

int root[N];
struct Seg {
	int l,r;
	int val,depth;
} seg[NN];
int scnt,n;

Seg *qur(int pos,int p,int lb=1,int rb=n)
{
	if(lb==rb) {
		return seg+p;
	}
	int mid=(lb+rb)>>1;
	if(pos>mid)
		return qur(pos,seg[p].r,mid+1,rb);
	else
		return qur(pos,seg[p].l,lb,mid);
}

Seg *alt(int pos,int p,int oldp,int lb=1,int rb=n)
{
	if(lb==rb) {
		seg[p]=seg[oldp];
		return seg+p;
	}
	int mid=(lb+rb)>>1;
	if(pos>mid) {
		seg[p].l=seg[oldp].l;
		seg[p].r=scnt++;
		return alt(pos,seg[p].r,seg[oldp].r,mid+1,rb);
	} else {
		seg[p].r=seg[oldp].r;
		seg[p].l=scnt++;
		return alt(pos,seg[p].l,seg[oldp].l,lb,mid);
	}
}

void build(int lb=1,int rb=n,int p=0)
{
	if(lb==rb) {
		seg[p].val=lb;
		seg[p].depth=1;
		return;
	}
	int mid=(lb+rb)>>1;
	seg[p].l=scnt++;
	build(lb,mid,seg[p].l);
	seg[p].r=scnt++;
	build(mid+1,rb,seg[p].r);
}

Seg *findrt(int p,int u)
{
	Seg *r=qur(u,p);
	while(r->val!=u) u=r->val,r=qur(r->val,p);
	return r;
}

int main()
{
	ios::sync_with_stdio(false);

	int m;
	cin>>n>>m;
	scnt=1;
	build();

	for(int i=1;i<=m;i++) {
		root[i]=root[i-1];

		int a,b;
		cin>>a>>b;
		Seg *r1=findrt(root[i],a),*r2=findrt(root[i],b);
		if(r1->val==r2->val) {
			int l=1,r=i;
			while(l<r) {
				int mid=(l+r)>>1;
				if(findrt(root[mid],a)->val==findrt(root[mid],b)->val) {
					r=mid;
				} else {
					l=mid+1;
				}
			}
			cout<<l-1<<endl;
		} else {
			if(r1->depth>r2->depth) swap(r1,r2);
			root[i]=scnt++;
			alt(r1->val,root[i],root[i-1])->val=r2->val;
			if(r1->depth==r2->depth) {
				int old=root[i];
				root[i]=scnt++;
				alt(r2->val,root[i],old)->depth++;
			}
		}
	}

	return 0;
}