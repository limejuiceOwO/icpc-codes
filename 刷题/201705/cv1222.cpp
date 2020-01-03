#include <iostream>
#include <algorithm>
#include <cstring>
#define N 105
using namespace std;

int n;
int match[N];
char vis[N];
char G[N][N];
pair<int,int> ans[N];

bool dfs(int u)
{
	vis[u]=1;
	for(int v=1;v<=n;v++) {
		if(G[u][v]&&(!match[v]||(!vis[match[v]]&&dfs(match[v])))) {
			match[v]=u;
			return true;
		}
	}
	return false;
}

int bimatch()
{
	int ans=0;
	for(int i=1;i<=n;i++) {
		memset(vis,0,sizeof(vis));
		if(dfs(i)) ans++;
	}
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	memset(G,1,sizeof(G));
	while(1) {
		int u,v;
		cin>>u>>v;
		if(u==0||v==0) break;
		G[u][v]=0;
	}
	if(bimatch()!=n) {
		cout<<"none"<<endl;
		return 0;
	}
	int cnt=0;
	for(int j=1;j<=n;j++) {
		int i=match[j];
		G[i][j]=0;
		match[j]=0;
		memset(vis,0,sizeof(vis));
		if(!dfs(i)) {
			ans[cnt++]=make_pair(i,j);
			match[j]=i;
		}
		G[i][j]=1;
	}
	if(!cnt) cout<<"none"<<endl;
	sort(ans,ans+cnt);//注意按x升序输出
	for(int i=0;i<cnt;i++) {
		cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	return 0;
}