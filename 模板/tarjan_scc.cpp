#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define N 1005
using namespace std;

vector<int> G[N];
int dfn[N],low[N],scc_fa[N];
char in_stk[N];
stack<int> stk;
int cnt=1;

void tarjan(int u)
{
	//cout<<"'"<<u<<endl;
	dfn[u]=low[u]=cnt++;
	stk.push(u);
	in_stk[u]=1;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		} else if(in_stk[v]) {
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]) {
		//cout<<"''"<<u<<endl;
		int uu;
		do {
			uu=stk.top();stk.pop();
			//if(scc_fa[uu]!=0) cout<<"''"<<uu<<endl;
			scc_fa[uu]=u;
			in_stk[uu]=0;
		} while(uu!=u);
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
	}
	//memset(vis,0,sizeof(vis));
	//memset(in_stk,0,sizeof(in_stk));
	//tarjan(1);
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++) {
		cout<<i<<" "<<scc_fa[i]<<endl;
	}
	return 0;
}