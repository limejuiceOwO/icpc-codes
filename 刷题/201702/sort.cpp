#include <iostream>
#define N 100005
#define NN 262147
using namespace std;

struct Operation {
	int t,l,r;
} opr[N];

int arr[N];
int val[NN],cov[NN];
int n;

void pushdown(int p,int lb,int rb)
{
	if(cov[p]) {
		const int mid=(lb+rb)>>1;
		cov[p<<1]=cov[p<<1|1]=cov[p];
		val[p<<1]=(mid-lb+1)*(cov[p]-1);
		val[p<<1|1]=(rb-mid)*(cov[p]-1);
		cov[p]=0;
	}
}

void build(int key,int p=1,int lb=1,int rb=n,bool init=true)
{
	static int idx;
	if(init) idx=0;
	cov[p]=0;
	if(lb==rb) {
		val[p]=(arr[idx++]>key)?1:0;
		return;
	}
	const int mid=(lb+rb)>>1;
	build(key,p<<1,lb,mid,false);
	build(key,p<<1|1,mid+1,rb,false);
	val[p]=val[p<<1]+val[p<<1|1];
}

int qur(int l,int r,int p=1,int lb=1,int rb=n)
{
	if(l>r||l>rb||r<lb) return 0;
	else if(l<=lb&&r>=rb) return val[p];
	else {
		const int mid=(lb+rb)>>1;
		pushdown(p,lb,rb);
		return qur(l,r,p<<1,lb,mid)+qur(l,r,p<<1|1,mid+1,rb);
	}
}

void cover(int l,int r,int v,int p=1,int lb=1,int rb=n)
{
	if(l>r||l>rb||r<lb) return;
	else if(l<=lb&&r>=rb) {
		val[p]=(rb-lb+1)*v;
		cov[p]=v+1;
	} else {
		const int mid=(lb+rb)>>1;
		pushdown(p,lb,rb);
		cover(l,r,v,p<<1,lb,mid);
		cover(l,r,v,p<<1|1,mid+1,rb);
		val[p]=val[p<<1]+val[p<<1|1];
	}
}

int main()
{
	ios::sync_with_stdio(false);
	int m,q;
	cin>>n>>m;
	for(int i=0;i<n;i++) cin>>arr[i];
	for(int i=0;i<m;i++) cin>>opr[i].t>>opr[i].l>>opr[i].r;
	cin>>q;
	int lb=1,rb=n+1;
	while(lb<rb) {
		int mid=(lb+rb)>>1;
		build(mid);
		for(int i=0;i<m;i++) {
			int l=opr[i].l,r=opr[i].r;
			int s=qur(l,r);
			//cout<<opr[i].t<<" "<<l<<" "<<r<<" "<<mid<<" "<<s<<endl;
			if(!opr[i].t) {
				cover(l,r-s,0);
				cover(r-s+1,r,1);
			} else {
				cover(l,l+s-1,1);
				cover(l+s,r,0);
			}
		}
		//cout<<qur(q,q)<<endl;
		if(qur(q,q)==0) rb=mid;
		else lb=mid+1;
	}
	cout<<lb<<endl;
	return 0;
}