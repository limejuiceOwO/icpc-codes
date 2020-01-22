#include <iostream>
#include <cstring>
#define N 105
using namespace std;

char graph[N][N];
char vis[N];
int match[N],_match[N];
int n,m;
int ln[N * N],col[N * N];

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
	ios::sync_with_stdio(false);
	int t = 1;
	while(1) {
		int k; cin >> n >> m >> k;
		if(cin.eof())
			return 0;
		memset(graph,0,sizeof(graph));
		memset(match,0,sizeof(match));
		for(int i = 0;i < k;i++) {
			cin >> ln[i] >> col[i];
			graph[ln[i]][col[i]] = 1;
		}
		int mx = bimatch(),imp = 0;
		memcpy(_match,match,sizeof(match));
		for(int i = 0;i < k;i++) {
			if(match[col[i]] != ln[i])
				continue;
			graph[ln[i]][col[i]] = 0;
			match[col[i]] = 0;
			memset(vis,0,sizeof(vis));
			if(!dfs(ln[i]))
				imp++;
			memcpy(match,_match,sizeof(match));
			graph[ln[i]][col[i]] = 1;
		}
		cout << "Board " << t++ << " have " << imp << " important blanks for " << mx << " chessmen." << endl;
	}
}