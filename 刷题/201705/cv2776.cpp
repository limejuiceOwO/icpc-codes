#include <iostream>
#include <algorithm>
#include <cstring>
#define N 205
using namespace std;

char G[N][N];
char vis[N];
int match[N];
int n,m;

bool dfs(int u)
{
	//if(!match[u]) return true;
	vis[u]=1;
	for(int v=1;v<=m;v++) {
		if(G[u][v]&&(!match[v]||(!vis[match[v]]&&dfs(match[v])))) {
			match[v]=u;
			return true;
		}
	}
	return false;
}

int bimatch()
{
	int res=0;
	for(int u=1;u<=n;u++) {
		memset(vis,0,sizeof(vis));
		if(dfs(u)) res++;
	}
	return res;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		while(1) {
			int v;
			cin>>v;
			if(!v) break;
			G[i][v]=1;
		}
	}
	cout<<bimatch()<<endl;
	return 0;
}