//#include <iostream>
#include <cstdio>
#include <cstring>
#define N 305
using namespace std;

char graph[N][N];
char vis[N];
int match[N];
int n,m;

bool dfs(int u)
{
	vis[u] = 1;
	for(int v = 1;v <= m;v++) {
		if(graph[u][v] && (!match[v] || (!vis[match[v]] && dfs(match[v])))) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int bimatch()
{
	int res = 0;
	for(int u = 1;u <= n;u++) {
		memset(vis,0,sizeof(vis));
		if(dfs(u)) res++;
	}
	return res;
}

int main()
{
	//ios::sync_with_stdio(false);
	int t; scanf("%d",&t);//cin >> t;
	while(t--) {
		//cin >> n >> m;
		scanf("%d%d",&n,&m);
		memset(graph,0,sizeof(graph));
		memset(match,0,sizeof(match));
		for(int u = 1;u <= n;u++) {
			int q; scanf("%d",&q);//cin >> q;
			while(q--) {
				int v; scanf("%d",&v);//cin >> v;
				graph[u][v] = 1;
			}
		}
		if(bimatch() == n)
			puts("YES");
			//cout << "YES" << endl;
		else
			puts("NO");
			//cout << "NO" << endl;
	}
	return 0;
}