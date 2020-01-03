#include <iostream>
#include <algorithm>
#include <vector>
#define N 30005
#define NN 65541
using namespace std;

vector<int> G[N];
int w[N],top[N],repr[N],fa[N],depth[N],size[N],wson[N];
int mx[NN],sum[NN];
int n;

void alt(int pos,int val,int p=1,int lb=1,int rb=n)
{
	if(lb==rb) {
		sum[p]=mx[p]=val;
		return;
	}

	int mid=(lb+rb)>>1;
	if(pos<=mid) alt(pos,val,p<<1,lb,mid);
	else alt(pos,val,p<<1|1,mid+1,rb);

	mx[p]=max(mx[p<<1],mx[p<<1|1]);
	sum[p]=sum[p<<1]+sum[p<<1|1];
}

int qmax(int l,int r,int p=1,int lb=1,int rb=n)
{
	if(l<=lb&&r>=rb)
		returhn mx[p];

	if(l>rb||r<lb)
		return -100000000;

	int mid=(lb+rb)>>1;
	return max(qmax(l,r,p<<1,lb,mid),qmax(l,r,p<<1|1,mid+1,rb));
}

int qsum(int l,int r,int p=1,int lb=1,int rb=n)
{
	if(l<=lb&&r>=rb)
		return sum[p];

	if(l>rb||r<lb)
		return 0;

	int mid=(lb+rb)>>1;
	return qsum(l,r,p<<1,lb,mid)+qsum(l,r,p<<1|1,mid+1,rb);
}

void dfs1(int u)
{
	int mxsize=-1,mxv=0;
	size[u]=1;

	for(int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa[u]) continue;

		depth[v]=depth[u]+1;
		fa[v]=u;
		dfs1(v);
		size[u]+=size[v];

		if(size[v]>mxsize) {
			mxsize=size[v];
			mxv=v;
		}
	}

	wson[u]=mxv;
}

void dfs2(int u)
{
	static int cnt=1;

	repr[u]=cnt++;
	alt(repr[u],w[u]);

	if(wson[u]) {
		top[wson[u]]=top[u];
		dfs2(wson[u]);
	}

	for(int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa[u]||v==wson[u]) continue;

		top[v]=v;
		dfs2(v);
	}
}

int query(int type,int u,int v) //0->max,1->sum
{
	int ans=type?0:-100000000;

	while(top[u]!=top[v]) {
		if(depth[top[u]]<depth[top[v]])
			swap(u,v);

		if(!type)
			ans=max(ans,qmax(repr[top[u]],repr[u]));
		else
			ans+=qsum(repr[top[u]],repr[u]);

		u=fa[top[u]];
	}

	if(depth[u]>depth[v]) swap(u,v);
	if(!type)
		ans=max(ans,qmax(repr[u],repr[v]));
	else 
		ans+=qsum(repr[u],repr[v]);

	return ans;
}

int main()
{
	ios::sync_with_stdio(false);

	cin>>n;

	for(int i=0;i<n-1;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for(int i=1;i<=n;i++)
		cin>>w[i];

	top[1]=fa[1]=1;
	dfs1(1);
	dfs2(1);

	int m;
	cin>>m;

	while(m--) {
		char cmd[10];
		int a,b;
		cin>>cmd>>a>>b;

		if(cmd[0]=='C') {
			alt(repr[a],b);
		} else if(cmd[0]=='Q') {
			if(cmd[1]=='M')
				cout<<query(0,a,b)<<endl;
			else if(cmd[1]=='S')
				cout<<query(1,a,b)<<endl;
		}
	}

	return 0;
}