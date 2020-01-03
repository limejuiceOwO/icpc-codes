#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define N 200005
#define P 10007
using namespace std;

vector<int> G[N];
long long w[N];
long long ans1,ans2;

void dfs(int u,int fa)
{
	long long ma=w[fa],mb=0;
	long long sum=w[fa],sum2=-w[fa]*w[fa];
	for(int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u);
		if(w[v]>mb) mb=w[v];
		if(ma<mb) swap(ma,mb);
		sum+=w[v];
		sum2-=w[v]*w[v];
	}
	if(G[u].size()>1) ans2=max(ans2,ma*mb);
	ans1=(sum*sum+sum2+ans1)%P;
}

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin>>n;

	for(int i=0;i<n-1;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for(int i=1;i<=n;i++)
		cin>>w[i];

	dfs(1,0);

	cout<<ans2<<" "<<ans1<<endl;
	return 0;
}