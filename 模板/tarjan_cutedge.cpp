#include <vector>
#include <cstring>
#include <algorithm>

int dfn[N],low[N],stack[N];
int stackTop,dfnTop,idTop;
int grpID[N];
vector<int> graph[N]; //must be an undirected graph
typedef vector<int>::iterator Iter;
//point compression related objects
vector<int> compGraph[N]; //a tree

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

void cutedge(int n) {
	dfnTop = idTop = 0;
	memset(dfn,0,sizeof(dfn));
	for(int i = 1;i <= n;i++) {
		if(!dfn[i])
			ce_dfs(i,0);
	}
}

void cutedge_compression(int n) {
	cutedge(n);
	for(int u = 1;u <= n;u++) {
		for(Iter it = graph[u].begin();it != graph[u].end();++it) {
			if(grpID[u] != grpID[*it]) {
				compGraph[grpID[u]].push_back(grpID[*it]);
			}
		}
	}
}