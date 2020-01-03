#include <iostream>
#include <algorithm>
#include <vector>
#define N 6005
using namespace std;

int w[N];
int d[N][2];
bool fa[N];
vector<int> G[N];

void dp(int u)
{
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		dp(v);
		d[u][0]+=max(d[v][0],d[v][1]);
		d[u][1]+=d[v][0];
	}
	d[u][1]+=w[u];
}

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>w[i];
	for(int i=0;i<n-1;i++) {
		int k,l;
		cin>>l>>k;
		fa[l]=true;
		G[k].push_back(l);
	}

	for(int i=1;i<=n;i++) {
		if(!fa[i]) {
			dp(i);
			cout<<max(d[i][0],d[i][1])<<endl;
			break;
		}
	}

	return 0;
}