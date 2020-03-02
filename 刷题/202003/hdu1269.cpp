#include <iostream>
#include <vector>
#include <cstring>
#define N 10005
using namespace std;

int dfn[N],low[N],stack[N];
bool inStack[N];
int stackTop,dfnTop,idTop;
int sccID[N];
vector<int> graph[N];
typedef vector<int>::iterator Iter;

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

int main()
{
	ios::sync_with_stdio(false);
	while(1) {
		int n,m; cin >> n >> m;
		if(n == 0)
			break;
		for(int i = 1;i <= n;i++)
			graph[i].clear();
		for(int i = 0;i < m;i++) {
			int u,v; cin >> u >> v;
			graph[u].push_back(v);
		}
		tarjan(n);
		if(idTop == 1) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	return 0;
}