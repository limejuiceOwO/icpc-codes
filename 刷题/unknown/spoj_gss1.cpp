#include<bits/stdc++.h>
#define N 50000
using namespace std;
struct Node {
	long long lm,rm,m,sum;	
} tree[4*N];

void build(int n,int l,int r,int p)
{
	if(r<=l+1) {
		int num;
		cin>>num;
		tree[p]=(Node){num,num,num,num};
		return;
	} else if(a>=l&&b<=r) {
		lm=tree[p].lm;
		rm=tree[p].rm;
		return tree[p].m;
	} else {
		long long llm,lrm,rlm,rrm,ml,mr;
		const int mid=l+(r-l)>>1,lch=p*2+1,rch=p*2+2;
		ml=build(n,l,mid,lch,llm,lrm);
		mr=query(n,mid,r,rch,rlm,rrm);
		lm=max(0,max(tree[lch].sum+rlm,llm));
		rm=max(0,max(tree[rch].sum+lrm,rrm));
		return max(0,lrm+rlm);
	}
}

long long query(int a,int b,int l,int r,int p,long long &lm,long long &rm)
{
	if(b<=l||a>=r) {
		lm=rm=-1;
		return -1;
	} else if(a>=l&&b<=r) {
		lm=tree[p].lm;
		rm=tree[p].rm;
		return tree[p].m;
	} else {
		long long llm,lrm,rlm,rrm,ml,mr;
		const int mid=l+(r-l)>>1,lch=p*2+1,rch=p*2+2;
		ml=query(a,b,l,mid,lch,llm,lrm);
		mr=query(a,b,mid,r,rch,rlm,rrm);
		lm=max(0,max(tree[lch].sum+rlm,llm));
		rm=max(0,max(tree[rch].sum+lrm,rrm));
		return max(0,lrm+rlm);
	}
}

int main()
{
	cin.sync_with_stdio(false);
	int n,q;
	long long null;
	cin>>n;
	build(n,0,n,0,null,null);
	cin>>q;
	while(q--) {
		int a,b;
		cin>>a>>b;
		query(a-1,b,0,n,0,null,null);
	}
	return 0;
}
