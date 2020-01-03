#include <iostream>
#include <algorithm>
#include <vector>
#define N 100005
#define NN 262149
#define INF 1000000005
using namespace std;

int arr[N],lazy[NN],minval[NN],sum[NN]; 
int dfn[N],size[N],h[N];
int n;
vector<int> G[N];

void build(int l=1,int r=n,int p=1)
{
	if(l==r) {
		minval[p]=(arr[l]<=0) ? INF : arr[l];
		sum[p]=(arr[l]<=0) ? 0 : 1;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	sum[p]=sum[p<<1]+sum[p<<1|1];
	minval[p]=min(minval[p<<1],minval[p<<1|1]);
}

int qur(int l,int r,int lb=1,int rb=n,int p=1)
{
	if(l>rb||r<lb)
		return 0;
	if(l<=lb&&r>=rb)
		return sum[p];

	int mid=(lb+rb)>>1;
	return qur(l,r,lb,mid,p<<1)+qur(l,r,mid+1,rb,p<<1|1);
}

void alter(int pos,int lb=1,int rb=n,int p=1)
{
	if(lb==rb) {
		sum[p]=0;
		return;
	}
	int mid=(lb+rb)>>1;
	if(pos<=mid)
		alter(pos,lb,mid,p<<1);
	else
		alter(pos,mid+1,rb,p<<1|1);
	sum[p]=sum[p<<1]+sum[p<<1|1];
}

void pushdown(int p)
{
	if(minval[p]==INF)
		return;
	minval[p<<1]-=lazy[p];
	minval[p<<1|1]-=lazy[p];
	lazy[p]=0;
}

void rec_dec(int p,int l,int r,int v)
{
	if(minval[p]==INF)
		return;
	pushdown(p);
	if(minval[p]>v) {
		minval[p]-=v;
		lazy[p]+=v;
	} else if(l==r) {
		minval[p]=INF;
		alter(l);
	} else {
		int mid=(l+r)>>1;
		rec_dec(p<<1,l,mid,v);
		rec_dec(p<<1|1,mid+1,r,v);
		minval[p]=min(minval[p<<1],minval[p<<1|1]);
	}
}

void dec(int l,int r,int v,int lb=1,int rb=n,int p=1)
{
	if(l>rb||r<lb)
		return;
	if(l<=lb&&r>=rb) {
		rec_dec(p,lb,rb,v);
		return;
	}
	int mid=(lb+rb)>>1;
	pushdown(p);
	dec(l,r,v,lb,mid,p<<1);
	dec(l,r,v,mid+1,rb,p<<1|1);
}

void dfs(int u=0,int fa=0)
{
	static int d=1;
	size[u]=1;
	dfn[u]=d++;
	arr[dfn[u]]=h[u];
	for(int i=0;i<n;i++) {
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u);
		size[u]+=size[v];
	}
}

int main()
{
	cin>>n;

	h[0]=-1;
	for(int i=1;i<n;i++) {
		int f;
		cin>>f>>h[i];
		G[f].push_back(i);
	}
	dfs();
	build();

	int q;
	cin>>q;
	while(q--) {
		int cmd,a,b;
		cin>>cmd;
		if(cmd==1) {
			cin>>a;
			if(size[a]>1)
				cout<<qur(dfn[a]+1,dfn[a]+size[a]-1);
			else
				cout<<"0"<<endl;
		} else if(cmd==2) {
			cin>>a>>b;
			if(size[a]>1)
				dec(dfn[a]+1,dfn[a]+size[a]-1,b);
		}
	}

	return 0;
}