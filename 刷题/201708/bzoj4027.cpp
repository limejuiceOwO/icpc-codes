#include <cstdio>
#include <algorithm>
#include <vector>
#define N 2000005
using namespace std;

vector<int> G[N];
int w[N],siz[N];
int m,ans;

void dfs(int u)
{
	static int arr[N];
	for(unsigned int i=0;i<G[u].size();i++) {
		dfs(G[u][i]);
	}

	siz[u]=w[u]+G[u].size();
	//cout<<u<<" "<<siz[u]<<endl;
	for(unsigned int i=0;i<G[u].size();i++)
		arr[i]=siz[G[u][i]];
	sort(arr,arr+G[u].size());

	for(unsigned int i=0;i<G[u].size();i++) {
		if(siz[u]+arr[i]-1>m) break;
		ans++;
		siz[u]+=arr[i]-1;
	}
}

int main()
{
	int n;
	scanf("%d%d",&n,&m);

	for(int i=0;i<n;i++)
		scanf("%d",&w[i]);

	for(int i=0;i<n;i++) {
		int c,v;
		scanf("%d",&c);
		for(int j=0;j<c;j++) {
			scanf("%d",&v);
			G[i].push_back(v);
		}
	}

	dfs(0);
	printf("%d\n",ans);
	return 0;
}