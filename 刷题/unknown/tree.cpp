#include<bits/stdc++.h>
#define N 200000
using namespace std;

long long tree[10*N];
long long add[10*N];
//long long add2[10*N];

int n;

void push(int idx,long long x)
{
	int p=0,l=0,r=n;
	while(r-l>1) {
		int mid=l+((r-l)>>1),left=(p<<1)+1,right=(p<<1)+2;
		tree[p]+=x;
		if(idx<mid) {
			p=left;
			r=mid;
		} else {
			p=right;
			l=mid;
		}
	}
	tree[p]+=x;
}

void addseg(int a,int b,long long x,int p,int l,int r)
{
	if(a<=l&&b>=r) {
		add[p]+=x;
		//add2[p]+=(r-l)*x;
		tree[p]+=(r-l)*x;
	} else if(b<=l||a>=r) {
		return;
	} else {
		const int mid=l+((r-l)>>1),left=(p<<1)+1,right=(p<<1)+2;
		//add2[p]+=(min(b,r)-max(a,l))*x;
		tree[p]+=(min(b,r)-max(a,l))*x;
		addseg(a,b,x,left,l,mid);
		addseg(a,b,x,right,mid,r);
	}
}

long long query(int a,int b,int p,int l,int r)
{
	if(a<=l&&b>=r) {
		return tree[p];
	} else if(b<=l||a>=r) {
		return 0;
	} else {
		const int mid=l+((r-l)>>1),left=(p<<1)+1,right=(p<<1)+2;
		return add[p]*(min(b,r)-max(a,l))+query(a,b,left,l,mid)+query(a,b,right,mid,r);
	}
}


int main()
{
	cin.sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++) {
		int x;
		cin>>x;
		push(i,x);
	}
	int q;
	cin>>q;
	while(q--) {
		int c,a,b,x;
		cin>>c;
		if(c==1) {
			cin>>a>>b>>x;
			addseg(a-1,b,x,0,0,n);
		} else {
			cin>>a>>b;
			cout<<query(a-1,b,0,0,n)<<endl;
		}
	}
	return 0;
}
