//强连通分量模板题
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define N 5005
using namespace std;

struct Ans {
	vector<int> ans;//vector<int> *ans;
	bool operator <(const Ans &rhs) const {
		return ans.size()==rhs.ans.size()?ans[0]<rhs.ans[0]:ans.size()>rhs.ans.size();
	}
} ans[N];

vector<int> G[N];
stack<int> stk;
int dfn[N],low[N];
char in_stk[N];
int cnt=1,scnt=0;

void tarjan(int u)
{
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
		int uu;
		Ans &l=ans[scnt];
		do {
			uu=stk.top();stk.pop();
			l.ans.push_back(uu);
			in_stk[uu]=0;
		} while(uu!=u);
		sort(l.ans.begin(),l.ans.end());
		scnt++;
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int u,v,t;
		cin>>u>>v>>t;
		G[u].push_back(v);
		if(t==2) G[v].push_back(u);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	sort(ans,ans+scnt);
	/*for(int z=0;z<scnt;z++) {
		cout<<z<<" "<<ans[z].ans.size()<<endl;
		for(unsigned int i=0;i<ans[z].ans.size();i++) cout<<ans[z].ans[i]<<" ";
		cout<<endl;
	}*/
	cout<<ans[0].ans.size()<<endl;
	for(unsigned int i=0;i<ans[0].ans.size();i++) {
		cout<<ans[0].ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}