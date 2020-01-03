#include <cstdio>
#include <algorithm>
#include <vector>
#define N 1005
using namespace std;

int scnt=1;
int belong[N],major[N];
int stk[N],top;
int b;

vector<int> G[N];

void dfs(int u,int fa=0)
{
	int cur=top;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		dfs(v,u);
	}

	if(top-cur>=b) {
		while(top>cur) {
			belong[stk[top-1]]=scnt;
			top--;
		}
		major[scnt++]=u;
	}
	stk[top++]=u;
}

int main()
{
	int n;
	scanf("%d%d",&n,&b);

	if(n<b) {
		puts("0");
		return 0;
	}

	for(int i=0,u,v;i<n-1;i++) {
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1);

	while(top) {
		belong[stk[top-1]]=scnt-1;
		top--;
	}

	printf("%d\n",scnt-1);
	for(int i=1;i<=n;i++) {
		printf("%d ",belong[i]);
	}
	puts("");
	for(int i=1;i<scnt;i++) {
		printf("%d ",major[i]);
	}
	puts("");

	return 0;
}