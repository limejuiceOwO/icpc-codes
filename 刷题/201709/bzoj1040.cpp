#include <cstdio>
#include <algorithm>
#include <vector>
#define N 1000005
using namespace std;
typedef pair<int,int> pii;

vector<int> G[N];
vector<pii> ring;
long long dp[N][2];
int w[N],fa[N];
char vis[N];

int findrt(int u)
{
	return fa[u]==u ? u : fa[u]=findrt(fa[u]);
}

void solve(int u,int fa=0)
{
	vis[u]=1;
	dp[u][0]=0;
	dp[u][1]=w[u];
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		solve(v,u);
		dp[u][0]+=max(dp[v][0],dp[v][1]);
		dp[u][1]+=dp[v][0];
	}	
}

int main()
{
	int n;
	scanf("%d",&n);

	for(int i=1;i<=n;i++)
		fa[i]=i;

	for(int i=1;i<=n;i++) {
		int v;
		scanf("%d%d",&w[i],&v);
		if(findrt(i)==findrt(v)) { //ring or tree
			unsigned int j;
			for(j=0;j<G[i].size();j++) {
				if(G[i][j]==v) //tree
					break;
			}
			if(j==G[i].size())
				ring.push_back(make_pair(i,v));
		} else {
			G[i].push_back(v);
			G[v].push_back(i);
			fa[findrt(i)]=findrt(v);
		}
	}

	long long ans=0;
	for(unsigned int i=0;i<ring.size();i++) {
		long long u=ring[i].first,v=ring[i].second;
		solve(u);
		long long curans=dp[u][0];
		solve(v);
		curans=max(curans,dp[v][0]);
		ans+=curans;
	}

	for(int i=1;i<=n;i++) {
		if(!vis[i]) {
			solve(i);
			ans+=max(dp[i][0],dp[i][1]);
		}
	}

	printf("%lld\n",ans);
	return 0;
}