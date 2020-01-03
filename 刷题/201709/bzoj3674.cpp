//可持久化并查集+路径压缩
#include <cstdio>
#include <algorithm>
#define N 200005
#define NN 10000005
using namespace std;

int rt[N];
struct Seg {
	int l,r;
	int val;
} seg[NN];
int scnt,n;

int qur(int pos,int p,int lb=1,int rb=n)
{
	if(lb==rb) {
		return seg[p].val;
	}
	int mid=(lb+rb)>>1;
	if(pos>mid)
		return qur(pos,seg[p].r,mid+1,rb);
	else
		return qur(pos,seg[p].l,lb,mid);
}

void alt(int pos,int val,int p,int oldp,int lb=1,int rb=n)
{
	if(lb==rb) {
		seg[p].val=val;
		return;
	}
	int mid=(lb+rb)>>1;
	if(pos>mid) {
		seg[p].l=seg[oldp].l;
		seg[p].r=scnt++;
		alt(pos,val,seg[p].r,seg[oldp].r,mid+1,rb);
	} else {
		seg[p].r=seg[oldp].r;
		seg[p].l=scnt++;
		alt(pos,val,seg[p].l,seg[oldp].l,lb,mid);
	}
}

void build(int lb=1,int rb=n,int p=0)
{
	if(lb==rb) {
		seg[p].val=lb;
		return;
	}
	int mid=(lb+rb)>>1;
	seg[p].l=scnt++;
	build(lb,mid,seg[p].l);
	seg[p].r=scnt++;
	build(mid+1,rb,seg[p].r);
}

int findrt(int &p,int u)
{
	int r=qur(u,p);
	if(r==u) return r;
	r=findrt(p,r);
	int oldp=p;
	p=scnt++;
	alt(u,r,p,oldp);
	return r;
}

int main()
{
	int m;
	scanf("%d%d",&n,&m);
	scnt=1;
	build();

	int la=0;
	for(int i=1;i<=m;i++) {
		int op;
		scanf("%d",&op);
		if(op==1) {
			int a,b;
			scanf("%d%d",&a,&b);
			int r1=findrt(rt[i-1],a^la),r2=findrt(rt[i-1],b^la);
			rt[i]=rt[i-1];
			if(r1==r2) continue;
			rt[i]=scnt++;
			alt(r1,r2,rt[i],rt[i-1]);
		} else if(op==2) {
			int k;
			scanf("%d",&k);
			rt[i]=rt[k^la];
		} else if(op==3) {
			int a,b;
			scanf("%d%d",&a,&b);
			rt[i]=rt[i-1];
			if(findrt(rt[i],a^la)==findrt(rt[i],b^la)) {
				puts("1");
				la=1;
			} else {
				puts("0");
				la=0;
			}
		}
	}

	return 0;
}