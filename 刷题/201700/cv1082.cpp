#include<bits/stdc++.h>
#define N 262144
using namespace std;
long long tree[N+10];//a[i]-a[i-1]
long long tree2[N+10];//tree[i]*i
int n;

long long query(long long *tr,int idx)
{
	long long ans=0;
	while(idx) {
		ans+=tr[idx];
		idx-=(idx&-idx);
	}
	return ans;
}

void push(long long *tr,int idx,long long x)
{
	while(idx<=n) {
		tr[idx]+=x;
		idx+=(idx&-idx);
	}
}

int main()
{
	cin.sync_with_stdio(false);
	cin>>n;
	long long last=0;
	for(int i=1,x;i<=n;i++) {
		cin>>x;
		push(tree,i,x-last);
		push(tree2,i,i*(x-last));
		last=x;
	}
	int q;
	cin>>q;
	while(q--) {
		int c,a,b,x;
		cin>>c;
		if(c==1) {
			cin>>a>>b>>x;
			push(tree,a,x);
			push(tree,b+1,-x);
			push(tree2,a,a*x);
			push(tree2,b+1,-(b+1)*x);
		} else {
			cin>>a>>b;
			cout<<(b+1)*query(tree,b)-query(tree2,b)-(a*query(tree,a-1)-query(tree2,a-1))<<endl;
		}
	}
	return 0;
}
