#include <iostream>
#include <algorithm>
using namespace std;

char G[55][55];
int ans[55];

int main()
{
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++) ans[i-1]=i;
	while(1) {
		int u,v;
		cin>>u>>v;
		G[u][v]=G[v][u]=1;
		if(cin.eof()) break;
	}
	do {
		for(i=1;i<n;i++) {
			if(!G[ans[i-1]][ans[i]]) break;
		}
		if(i==n&&G[ans[0]][ans[n-1]]) {
			for(i=0;i<n;i++) cout<<ans[i]<<" ";
			cout<<endl;
			return 0;
		}
	} while(next_permutation(ans,ans+n));
	return 0;
}