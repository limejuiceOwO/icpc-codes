//ZJOI2007 矩阵游戏 二分图完美匹配
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 205
using namespace std;

int match[N];
char vis[N];
vector<int> G[N];

bool dfs(int u)
{
	vis[u]=1;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(!match[v]||(!vis[match[v]]&&dfs(match[v]))) { //注意编号从1开始，否则点0会和不存在搞混
			match[v]=u;
			return true;
		}
	}
	return false;
}

int bimatch(int n)
{
	int ans=0;
	memset(match,0,sizeof(match)); //每次匹配前注意清空match数组
	for(int u=1;u<=n;u++) {
		memset(vis,0,sizeof(vis));
		ans+=dfs(u);
	}

	return ans;
}

int main()
{
	int t,n;
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			G[i].clear();

		for(int i=1;i<=n;i++) {
			for(int j=1;j<=n;j++) {
				int c;
				scanf("%d",&c);
				if(c) G[i].push_back(j); //同一行/列上的1只会有1个被选中，所以把行列看作点，1看作边，求最大匹配
			}
		}

		if(bimatch(n)==n) {
			puts("Yes");
		} else {
			puts("No");
		}
	}

	return 0;
}