#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define N 300005
using namespace std;

typedef pair<int,bool> Edge;
int dfn[N],low[N],stack[N];
int stackTop,dfnTop,idTop;
int grpID[N];
vector<Edge> graph[N];
typedef vector<Edge>::iterator Iter;
//point compression related objects
vector<Edge> compGraph[N]; //a tree
bool mark[N];

void ce_dfs(int u,int fa) {
	dfn[u] = low[u] = ++dfnTop;
	stack[stackTop++] = u;
	for(Iter it = graph[u].begin();it != graph[u].end();++it) {
		int v = it -> first;
		if(v == fa)
			continue;
		if(!dfn[v]) {
			ce_dfs(v,u);
			low[u] = min(low[u],low[v]);
		} else { //v must be an ancestor of u
			low[u] = min(low[u],dfn[v]);
		}
	}
	if(dfn[u] == low[u]) { //u is the top node of a new group
		int idNew = ++idTop;
		while(stack[stackTop - 1] != u) {
			grpID[stack[--stackTop]] = idNew;
		}
		grpID[u] = idNew;
		stackTop--;
	}
}

void cutedge_compression(int n) {
	ce_dfs(1,0);
	for(int u = 1;u <= n;u++) {
		for(Iter it = graph[u].begin();it != graph[u].end();++it) {
			int v = it -> first;
			if(grpID[u] != grpID[v]) {
				compGraph[grpID[u]].push_back(make_pair(grpID[v],it -> second));
			} else if(it -> second) {
				mark[grpID[u]] = true;
			}
		}
	}
}

int st,ed;
char judge(int u,int fa) {
	if(u == grpID[ed]) {
		return mark[grpID[ed]] ? 2 : 1;
	}
	for(Iter it = compGraph[u].begin();it != compGraph[u].end();++it) {
		int v = it -> first;
		if(v == fa)
			continue;
		int r = judge(v,u);
		if(r == 2 || ((mark[u] || it -> second) && r == 1))
			return 2;
		else if(r == 1)
			return 1;
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(false);
	int n,m; cin >> n >> m;
	for(int i = 0;i < m;i++) {
		int u,v,a; cin >> u >> v >> a;
		graph[u].push_back(make_pair(v,(bool) a));
		graph[v].push_back(make_pair(u,(bool) a));
	}
	cin >> st >> ed;
	cutedge_compression(n);
	/*for(int i = 1;i <= n;i++)
		cout << grpID[i] << " ";
	cout << endl;*/

	if(judge(grpID[st],0) == 2) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}