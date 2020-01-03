#include <cstdio>
#include <algorithm>
#include <vector>
#define N 100005
#define NN 262147
using namespace std;

long long bit1[NN],bit2[NN],bit3[NN];
vector<int> G[N];
int dfn[N],dep[N],size[N];
long long w[N];

long long qur(long long *bit,int pos)
{
	long long ans=0;
	while(pos) {
		ans+=bit[pos];
		pos-=(pos&-pos);
	}
	return ans;
}

void _alt(long long *bit,int pos,long long val)
{
	while(pos<=NN) {
		bit[pos]+=val;
		pos+=(pos&-pos);
	}
}

void alt(long long *bit,int l,int r,long long val)
{
	_alt(bit,r+1,-val);
	_alt(bit,l,val);
}

void dfs(int u,int fa=0)
{
	static int cdfn=1;
	size[u]=1;
	dfn[u]=cdfn++;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs(v,u);
		size[u]+=size[v];
	}
}

int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&w[i]);
	}

	for(int i=0;i<n-1;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1);

	for(int i=1;i<=n;i++) {
		alt(bit1,dfn[i],dfn[i]+size[i]-1,w[i]);
	}

	while(q--) {
		int cmd,x;
		long long a;
		scanf("%d",&cmd);
		if(cmd==1) {
			scanf("%d%lld",&x,&a);
			alt(bit1,dfn[x],dfn[x]+size[x]-1,a);
		} else if(cmd==2) {
			scanf("%d%lld",&x,&a);
			alt(bit2,dfn[x],dfn[x]+size[x]-1,dep[x]*a);
			alt(bit3,dfn[x],dfn[x]+size[x]-1,a);
		} else if(cmd==3) {
			scanf("%d",&x);
			printf("%lld\n",qur(bit1,dfn[x])-qur(bit2,dfn[x])+qur(bit3,dfn[x])*(dep[x]+1));
		}
	}

	return 0;
}