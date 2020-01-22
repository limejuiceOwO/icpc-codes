#include <iostream>
#include <cstdio>
#include <cstring>
#define N 105
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
	ios::sync_with_stdio(false);
	while(1) {
		cin >> n; m = n;
		if(cin.eof())
			return 0;
		cin.get();
		memset(graph,0,sizeof(graph));
		memset(match,0,sizeof(match));
		for(int i = 1;i <= n;i++)
		{
			string ln; getline(cin,ln);
			for(int j = 0,p = 1;j < (int)ln.length();j += 2,p++) {
				if(ln[j] == '1')
					graph[i][p] = 1;
			}
		}
		if(bimatch() < n) {
			cout << "-1" << endl;
			continue;
		}
		int cnt = 0;
		static char swp[N][20];
		memset(vis,0,sizeof(vis));
		for(int i = 1;i <= n;i++) {
			if(!vis[i]) {
				int p = i,q;
				while(1) {
					vis[p] = 1;
					q = match[p];
					if(q == i)
						break;
					sprintf(swp[cnt++],"R %d %d",p,q);
					p = q;
				}
			}
		}
		cout << cnt << endl;
		for(int i = 0;i < cnt;i++) {
			cout << swp[i] << endl;
		}
	}
}