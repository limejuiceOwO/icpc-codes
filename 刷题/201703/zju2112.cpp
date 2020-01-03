//Dynamic Ranking 可修改主席树 树状数组
#include <iostream>
#include <algorithm>
#include <cstring>
#define LGN 17
#define N 50005
#define N2 65541
#define M 10005
using namespace std;

struct FTree {
	int val;
	FTree *ch[2];
} heap[N2+LGN*LGN*M];

FTree *bitarr[N];
int raw[N];
int n,cnt;

void _build(FTree *&p,int l,int r)
{
	p=heap+(cnt++);
	if(l<r) {
		int mid=(l+r)>>1;
		_build(p->ch[0],l,mid);
		_build(p->ch[1],mid+1,r);
	}
	p->val=0;
}

void build()
{
	_build(bitarr[0],1,n);
	for(int i=1;i<=n;i++) {
		bitarr[i]=heap+(cnt++);
		memcpy(bitarr[i],bitarr[0],sizeof(FTree));
	}
}

void alter(int pos,int x,int op)
{
	while(pos<=n) {
		FTree *oldp=bitarr[pos];
		FTree *p=bitarr[pos]=heap+(cnt++);
		int l=1,r=n;
		while(l<r) {
			int mid=(l+r)>>1,d=(x>mid)?1:0;
			p->val=oldp->val+op;
			p->ch[d^1]=oldp->ch[d^1];
			p->ch[d]=heap+(cnt++);
			oldp=oldp->ch[d];
			p=p->ch[d];
			if(d) l=mid+1;
			else r=mid;
		}
		p->val=oldp->val+op;
		pos+=pos&(-pos);
	}
}

int qur(int l,int r,int k)
{
	static FTree *node1[LGN],*node2[LGN];
	int p1=0,p2=0;
	l--;
	while(l>0) {
		node1[p1++]=bitarr[l];
		l-=l&(-l);
	}
	while(r) {
		node2[p2++]=bitarr[r];
		r-=r&(-r);
	}
	l=1,r=n;
	while(l<r) {
		int cnt1=0,cnt2=0;
		int mid=(l+r)>>1;
		for(int i=0;i<p1;i++) {
			cnt1+=node1[i]->ch[0]->val;
		}
		for(int i=0;i<p2;i++) {
			cnt2+=node2[i]->ch[0]->val;
			//cout<<i<<" "<<node2[i]->ch[0]->val<<endl;
		}
		//cout<<l<<" "<<r<<" "<<cnt1<<" "<<cnt2<<endl;
		//cout<<"A"<<endl;
		int d=(cnt2-cnt1)<k?1:0;
		if(d) {
			k-=cnt2-cnt1;
			l=mid+1;
		} else {
			r=mid;
		}
		for(int i=0;i<p1;i++) {
			node1[i]=node1[i]->ch[d];
		}
		for(int i=0;i<p2;i++) {
			node2[i]=node2[i]->ch[d];
		}
	}
	return l;
}

int main()
{
	int m;
	cin>>n>>m;
	int nn;
	for(nn=1;nn<n;nn<<=1);
	swap(n,nn);
	build();
	for(int i=1,x;i<=nn;i++) {
		cin>>x;
		alter(i,raw[i]=x,1);
	}
	while(m--) {
		char cmd[5];
		int l,r,k;
		cin>>cmd;
		if(cmd[0]=='Q') {
			cin>>l>>r>>k;
			cout<<qur(l,r,k)<<endl;
		} else {
			cin>>l>>k;
			alter(l,raw[l],-1);
			alter(l,k,1);
			raw[l]=k;
		}
	}
	return 0;
}