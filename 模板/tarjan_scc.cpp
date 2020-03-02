#include <vector>
#include <cstring>
#include <algorithm>

int dfn[N],low[N],stack[N];
bool inStack[N];
int stackTop,dfnTop,idTop;
int sccID[N];
vector<int> graph[N];
typedef vector<int>::iterator Iter;
//point compression related objects
vector<int> compGraph[N]; //a DAG

void tarjan_dfs(int u) {
	dfn[u] = low[u] = ++dfnTop;
	stack[stackTop++] = u;
	inStack[u] = true;
	for(Iter it = graph[u].begin();it != graph[u].end();++it) {
		int v = *it;
		if(!dfn[v]) {
			tarjan_dfs(v);
			low[u] = min(low[u],low[v]);
		} else if(inStack[v]) { //v is an ancestor of u
			low[u] = min(low[u],dfn[v]);
		} //otherwise v must be in another SCC which cannot reach u
	}
	if(dfn[u] == low[u]) { //u is the top node of a new SCC
		int idNew = ++idTop;
		while(stack[stackTop - 1] != u) { //the stack cannot be empty
			inStack[stack[stackTop - 1]] = false;
			sccID[stack[--stackTop]] = idNew;
		}
		inStack[u] = false;
		sccID[u] = idNew;
		stackTop--;
	}
}

void tarjan(int n) {
	dfnTop = idTop = 0; //no need to clear stack and id after a clear run
	memset(dfn,0,sizeof(dfn));
	for(int i = 1;i <= n;i++) {
		if(!dfn[i])
			tarjan_dfs(i);
	}
}

void tarjan_compression(int n) {
	tarjan(n);
	for(int u = 1;u <= n;u++) {
		for(Iter it = graph[u].begin();it != graph[u].end();++it) {
			if(sccID[u] != sccID[*it]) {
				compGraph[sccID[u]].push_back(sccID[*it]);
			}
		}
	}
	//optional,costs extra log(n) complexity
	for(int u = 1;u <= idTop;u++) {
		sort(compGraph[u].begin(),compGraph[u].end()); 
		unique(compGraph[u].begin(),compGraph[u].end());
	}
}