//POJ1741 Tree
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 10005
#define INF 1000000005
using namespace std;

vector<int> G[N],w[N];
int size[N],subpt[N];
char vis[N];
int n,sz,root,ans;

void getrt(int u,int fa=0)
{
	static int mnsize,sz;
	if(!fa) {
		sz=size[u];
		mnsize=INF;
	}

	int mxsize=0;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa||vis[v]) continue;
		getrt(v,u);
		mxsize=max(mxsize,size[v]);
	}
	if(max(mxsize,sz-size[u])<mnsize) {
		root=u;
		mnsize=max(mxsize,sz-size[u]);
	}
}

void dfs(int u,int fa,int d=0)
{
	static int pcnt;
	if(!d) pcnt=0;

	size[u]=1;
	subpt[pcnt++]=d;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa||vis[v]) continue;
		dfs(v,u,d+w[u][i]);
		size[u]+=size[v];
	}
}

int countpair(int arr[],int size,int k)
{
	int p1=0,p2=size-1,ans=0;

	sort(arr,arr+size);
	while(1) {
		while(p1<=p2&&arr[p1]+arr[p2]>k) p2--;
		if(p1>p2) break;
		ans+=p2-p1;
		p1++;
	}

	return ans;
}

void solve(int k,int u=root)
{
	//cout<<u<<endl;
	static int pt[N];
	int pcnt=0;
	vis[u]=1;

	pt[pcnt++]=0;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i],ww=w[u][i];
		if(vis[v]) continue;
		dfs(v,u);
		//cout<<"A"<<endl;
		for(int i=0;i<size[v];i++)
			pt[pcnt++]=subpt[i]+ww;
		ans-=countpair(subpt,size[v],k-2*ww);
	}

	ans+=countpair(pt,pcnt,k);

	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(vis[v]) continue;
		getrt(v);
		//cout<<"'"<<v<<" "<<root<<endl;
		solve(k);
	}
}

int main()
{
	ios::sync_with_stdio(false);

	while(1) {
		int k;
		cin>>n>>k;
		if(n+k==0) break;

		for(int i=1;i<=n;i++) {
			G[i].clear();
			w[i].clear();
		}
		ans=0;
		memset(vis,0,sizeof(vis));

		for(int i=1;i<n;i++) {
			int u,v,ww;
			cin>>u>>v>>ww;
			G[u].push_back(v);
			w[u].push_back(ww);
			G[v].push_back(u);
			w[v].push_back(ww);
		}

		dfs(1,0);
		getrt(1);
		solve(k);

		cout<<ans<<endl;
	}
	return 0;
}