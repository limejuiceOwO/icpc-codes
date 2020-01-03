//NOIP2015 运输计划 二分+树链剖分+差分数组
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 300005
#define M 300005
#define to first
#define dist second
using namespace std;

struct Route {
	int u,v,sum;
}route[M];

vector<pair<int,int> > G[N];
int fa[N],depth[N],size[N],w[N],l[N],top[N],repr[N];
int diff[N],sum[N];
int n,m,cnt,mxsum;

void dfs1(int u)
{
	int mxsize=-1;
	size[u]=1;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i].to;
		if(v==fa[u]) continue;
		fa[v]=u;
		depth[v]=depth[u]+1;
		l[v]=G[u][i].dist;
		dfs1(v);
		size[u]+=size[v];
		if(size[v]>mxsize) {
			w[u]=v;
			mxsize=size[v];
		}
	}
}

void dfs2(int u)
{
	if(!w[u]) return;
	top[w[u]]=top[u];
	repr[w[u]]=cnt++;
	sum[w[u]]=sum[u]+l[w[u]];
	dfs2(w[u]);
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i].to;
		if(v==fa[u]||v==w[u]) continue;
		top[v]=v;
		repr[v]=cnt++;
		sum[v]=l[v];
		dfs2(v);
	}
}

int getsum(int u,int v)
{
	int res=0;
	while(top[u]!=top[v]) {
		//cout<<"'"<<u<<" "<<v<<" "<<res<<endl;
		if(depth[top[u]]<depth[top[v]]) swap(u,v);
		res+=sum[u];
		u=fa[top[u]];
	}
	//cout<<"''"<<u<<" "<<v<<" "<<res<<endl;
	if(depth[u]<depth[v]) swap(u,v);
	return res+sum[u]-sum[v];
}

bool check(int mx)
{
	memset(diff,0,sizeof(diff));
	int ecnt=0;
	for(int i=0;i<m;i++) {
		Route &rt=route[i];
		if(rt.sum<=mx) continue;
		ecnt++;
		int u=rt.u,v=rt.v;
		while(top[u]!=top[v]) {
			if(depth[top[u]]<depth[top[v]]) swap(u,v);
			diff[repr[u]+1]--;
			diff[repr[top[u]]]++;
			u=fa[top[u]];
		}
		if(u==v) continue;
		if(depth[u]<depth[v]) swap(u,v);
		diff[repr[u]+1]--;
		diff[repr[w[v]]]++;
	}
	//cout<<ecnt<<endl;
	for(int i=1;i<n;i++) diff[i]+=diff[i-1];
	//for(int i=0;i<n;i++) cout<<diff[i]<<" ";
	//cout<<endl;
	for(int i=1;i<n;i++) {
		if(diff[repr[i]]>=ecnt&&mxsum-l[i]<=mx) return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0,u,v,w;i<n-1;i++) {
		cin>>u>>v>>w;
		G[u].push_back(make_pair(v,w));
		G[v].push_back(make_pair(u,w));
	}
	cnt=fa[1]=top[1]=1;
	dfs1(1);
	dfs2(1);
	mxsum=-1;
	for(int i=0;i<m;i++) {
		cin>>route[i].u>>route[i].v;
		route[i].sum=getsum(route[i].u,route[i].v);
		mxsum=max(mxsum,route[i].sum);
		//cout<<route[i].sum<<endl;
	}
	int l=0,r=mxsum;
	while(l<r) {
		int mid=l+((r-l)>>1);
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l<<endl;
	return 0;
}