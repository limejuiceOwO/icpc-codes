//树 树形dp（？）
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define N 105
using namespace std;

int d[N][2][2];//d[u][lighted?][toggled?]
vector<int> G[N];

void dp(int u,int fa)
{
	d[u][0][0]=0;d[u][1][1]=1;d[u][1][0]=d[u][0][1]=100000;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		int t[2][2];
		if(v==fa) continue;
		dp(v,u);
		memcpy(t,d[u],sizeof(t));
		d[u][0][0]=min(t[0][0]+d[v][1][0],t[0][1]+d[v][1][1]);
		d[u][0][1]=min(t[0][1]+d[v][1][0],t[0][0]+d[v][1][1]);
		d[u][1][1]=min(t[1][0]+d[v][0][1],t[1][1]+d[v][0][0]);
		d[u][1][0]=min(t[1][1]+d[v][0][1],t[1][0]+d[v][0][0]);
	}
}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<n;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dp(1,-1);
	cout<<min(d[1][1][0],d[1][1][1])<<endl;
	return 0;
}