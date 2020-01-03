#include <iostream>
#include <algorithm>
#include <vector>
#define N 300005
using namespace std;

vector<int> G[N];
char occur[N];
int dp[N][2];
int cdfn;

void mark(int u)
{
	vis[u]=1;

	for(int i=0;i<G[u].size();i++) {
		if(vis[v]) continue;
		
	}
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		int v;
		cin>>v;
		occur[v]=true;
		G[i].push_back(v);
		G[v].push_back(i);
	}

	for(int i=0;i<n;i++) {
		dp[i][1]=1;
		if(!occur[i]) {
			mark(i);
		}
	}

	int ans=0;
	for(int i=0;i<n;i++) {
		if(!vis[i]) {
			dfs(i);
			ans+=max(dp[i][0],dp[i][1]);
		}
	}

	cout<<ans<<endl;
	return 0;
}