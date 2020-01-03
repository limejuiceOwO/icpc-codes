#include <iostream>
#include <algorithm>
using namespace std;
#define N 30005

int fa[N],size[N],dist[N];

int root(int u)
{
	if(u==fa[u]) return u;
	int r=root(fa[u]);
	dist[u]+=dist[fa[u]];
	return fa[u]=r;
}

int main()
{
	cin.sync_with_stdio(false);
	int m;
	cin>>m;
	for(int i=0;i<N;i++) {
		fa[i]=i;
		size[i]=1;
		//dist[i]=0;
	}
	while(m--) {
		string cmd;
		int a,b;
		cin>>cmd>>a>>b;
		int r1=root(a),r2=root(b);
		if(cmd[0]=='M') {
			if(r1==r2) continue;
			dist[r1]=size[r2];
			size[r2]+=size[r1];
			fa[r1]=r2;
		} else if(cmd[0]=='C') {
			if(r1==r2) cout<<abs(dist[a]-dist[b])-1<<endl;
			else cout<<"-1"<<endl;
		}
	}
	return 0;
}