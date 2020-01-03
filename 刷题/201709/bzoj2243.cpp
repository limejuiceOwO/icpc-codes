//SDOI2011 染色 树链剖分+线段树 4kbの噩梦
//#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define N 100005
#define NN 262147
using namespace std;

struct Seg {
	int lc,rc,val,cov;
}seg[NN];

int dfn[N],top[N],fa[N],dep[N],siz[N],wson[N];
int w[N],w2[N];
int n;
vector<int> G[N];

void dfs1(int u) //最好加个编号，免得写成dfs
{
	int mxsize=-1;
	siz[u]=1;

	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa[u]) continue;
		dep[v]=dep[u]+1;
		fa[v]=u;
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[v]>mxsize) {
			mxsize=siz[v];
			wson[u]=v;
		}
	}
}

void dfs2(int u)
{
	static int cdfn=0;
	dfn[u]=cdfn++;
	w2[dfn[u]]=w[u];

	if(wson[u]>0) {
		top[wson[u]]=top[u];
		dfs2(wson[u]);
	}

	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa[u]||v==wson[u]) continue;
		top[v]=v;
		dfs2(v);
	}
}

void build(int lb=0,int rb=n-1,int p=1)
{
	if(lb==rb) {
		seg[p].lc=seg[p].rc=w2[lb];
		seg[p].val=1;
		return;
	}

	int mid=(lb+rb)>>1;
	build(lb,mid,p<<1);
	build(mid+1,rb,p<<1|1);
	seg[p].val=seg[p<<1].val+seg[p<<1|1].val-(seg[p<<1].rc==seg[p<<1|1].lc);
	seg[p].lc=seg[p<<1].lc;
	seg[p].rc=seg[p<<1|1].rc;
}

void pushdown(int p)
{
	if(seg[p].cov) {
		seg[p<<1].cov=seg[p<<1|1].cov=seg[p].cov;
		seg[p<<1].val=seg[p<<1|1].val=1;
		seg[p<<1].lc=seg[p<<1].rc=seg[p<<1|1].lc=seg[p<<1|1].rc=seg[p].cov;
		seg[p].cov=0;
	}
}

int qur(int l,int r,int &lc,int &rc,int lb=0,int rb=n-1,int p=1)
{
	//if(lb==0&&rb==n-1) cout<<"'Q"<<l<<" "<<r<<endl;
	if(lb>r||rb<l) {
		lc=rc=0;
		return 0;
	}
	//if(l<=rb&&r>=rb) { //实力眼瞎，看了n遍都没发现......
	if(l<=lb&&r>=rb) {
		lc=seg[p].lc;
		rc=seg[p].rc;
		return seg[p].val;
	}

	int mid=(lb+rb)>>1,t1,t2;
	pushdown(p);
	int ans=qur(l,r,lc,t1,lb,mid,p<<1)+qur(l,r,t2,rc,mid+1,rb,p<<1|1)-(l<=mid&&r>mid&&seg[p<<1].rc==seg[p<<1|1].lc);
	if(rc==0) rc=t1;
	if(lc==0) lc=t2;
	return ans;
}

void alt(int l,int r,int c,int lb=0,int rb=n-1,int p=1)
{
	//if(lb==0&&rb==n-1) cout<<"'A"<<l<<" "<<r<<endl;
	if(lb>r||rb<l) {
		return;
	}

	if(l<=lb&&r>=rb) {
		seg[p].val=1;
		seg[p].lc=seg[p].rc=seg[p].cov=c;
		return;
	}

	int mid=(lb+rb)>>1;
	pushdown(p);
	alt(l,r,c,lb,mid,p<<1);
	alt(l,r,c,mid+1,rb,p<<1|1);
	seg[p].val=seg[p<<1].val+seg[p<<1|1].val-(seg[p<<1].rc==seg[p<<1|1].lc);
	seg[p].lc=seg[p<<1].lc;
	seg[p].rc=seg[p<<1|1].rc;
}

int qur_chain(int u,int v)
{
	int ans=0,lastc[2];
	int lc,rc;
	lastc[0]=lastc[1]=0;

	while(top[u]!=top[v]) {
		//cout<<"A"<<endl;
		//cout<<"'"<<u<<" "<<v<<" "<<lastc[0]<<" "<<lastc[1]<<endl;
		if(dep[top[u]]>dep[top[v]]) {
			ans+=qur(dfn[top[u]],dfn[u],lc,rc);
			u=fa[top[u]];
			//cout<<lc<<" "<<rc<<" "<<ans<<endl;
			if(lastc[0]==rc) ans--;
			lastc[0]=lc;
		} else {
			ans+=qur(dfn[top[v]],dfn[v],lc,rc);
			v=fa[top[v]];
			//cout<<lc<<" "<<rc<<" "<<ans<<endl;
			if(lastc[1]==rc) ans--;
			lastc[1]=lc;
		}
	}

	if(dep[u]<dep[v]) {
		ans+=qur(dfn[u],dfn[v],lc,rc);
		//cout<<"''"<<u<<" "<<v<<" "<<lastc[0]<<" "<<lastc[1]<<endl;
		//cout<<lc<<" "<<rc<<" "<<ans<<endl;
		if(lastc[1]==rc) ans--;
		if(lastc[0]==lc) ans--;
	} else {
		ans+=qur(dfn[v],dfn[u],lc,rc);
		//cout<<"''"<<lc<<" "<<rc<<endl;
		//cout<<lc<<" "<<rc<<" "<<ans<<endl;
		if(lastc[0]==rc) ans--;
		if(lastc[1]==lc) ans--;
	}
	return ans;
}

void alt_chain(int u,int v,int c)
{
	while(top[u]!=top[v]) {
		//cout<<"'"<<u<<" "<<v<<endl;
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		alt(dfn[top[u]],dfn[u],c);
		u=fa[top[u]];
	}
	
	if(dep[u]>dep[v]) swap(u,v);
	alt(dfn[u],dfn[v],c);
}

int main()
{
	int m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	for(int i=0;i<n-1;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	top[1]=1;
	dfs1(1);
	dfs2(1);
	build();

	char cmd[10];
	for(int i=0,u,v,c;i<m;i++) {
		scanf("%s",cmd);
		if(cmd[0]=='C') {
			scanf("%d%d%d",&u,&v,&c);
			alt_chain(u,v,c);
		} else if(cmd[0]=='Q') {
			scanf("%d%d",&u,&v);
			printf("%d\n",qur_chain(u,v));
		}
	}

	return 0;
}