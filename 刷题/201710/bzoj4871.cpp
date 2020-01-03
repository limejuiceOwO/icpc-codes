#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define N 100005
using namespace std;

int dp[N][6];
vector<int> G[N];

void dfs(int u,int fa)
{
	static int cur[6];
	memset(dp[u],0x80,sizeof(dp[0]));
	int m1=-1000000;
	for(int i=0,p=0;i<(int)G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u);
		memcpy(cur,dp[u],sizeof(cur)); //改成dp都能过样例...
		dp[u][0]=max(cur[0]+1,dp[v][0]+p);
		dp[u][1]=max(cur[1]+1,dp[v][1]+p);
		dp[u][1]=max(dp[u][1],max(cur[4],cur[5])+dp[v][0]);
		dp[u][1]=max(dp[u][1],max(dp[v][4],dp[v][5])+cur[0]);
		dp[u][2]=max(cur[2],cur[4]+dp[v][4]);
		dp[u][2]=max(dp[u][2],dp[v][3]+1);
		dp[u][3]=max(cur[3]+1,cur[1]+dp[v][0]);
		dp[u][3]=max(dp[u][3],cur[5]+max(dp[v][4],dp[v][5]));
		dp[u][4]=max(cur[4],dp[v][4]);
		dp[u][4]=max(dp[u][4],dp[v][5]+1);
		dp[u][5]=max(cur[5]+1,cur[0]+dp[v][0]);
		m1=max(m1,max(dp[v][4],dp[v][5]));
		p++;
	}
	int sz=G[u].size()-(bool)fa;
	dp[u][0]=max(dp[u][0],sz);
	dp[u][1]=max(dp[u][1],sz-1+m1);
	dp[u][5]=max(dp[u][5],sz);
	dp[u][5]=max(dp[u][5],dp[u][0]);
	dp[u][3]=max(dp[u][3],sz-1+m1);
	dp[u][3]=max(dp[u][3],dp[u][1]);
	dp[u][3]=max(dp[u][3],dp[u][5]);

//	cout<<"'"<<u<<" ";
//	for(int i=0;i<6;i++) {
//		cout<<dp[u][i]<<" ";
	//}
	//cout<<endl;
}

int main()
{
	int t,x;
	scanf("%d%d",&t,&x);
	while(t--) {
		int n;
		scanf("%d",&n);
		for(int i=0;i<x;i++)
			scanf("%*d%*d");
		for(int i=0;i<=n;i++)
			G[i].clear();
		for(int i=0,u,v;i<n-1;i++) {
			scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}

		dfs(1,0);
		printf("%d\n",max(dp[1][2],dp[1][3]));
	}
	return 0;
}