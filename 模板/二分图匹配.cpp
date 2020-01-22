#include <cstring>

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

int bimatch() // all edges are one-sided,do not add reverse edges into the graph!
{
	int res = 0;
	for(int u = 1;u <= n;u++) {
		memset(vis,0,sizeof(vis));
		if(dfs(u)) res++;
	}
	return res;
}