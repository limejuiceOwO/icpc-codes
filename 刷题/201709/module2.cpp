#include <iostream>
#include <algorithm>
#include <vector>
#define N 1000005
using namespace std;

vector<int> G[N];
char vis[N];
long long r,p;
long long fact[N];

void dfs(int u,int fa=0)
{
	vis[u]=1;
	int cnt=0,bcnt=0;
	for(unsigned int i=0;i<G[u].size();i++) {
		int v=G[u][i];
		if(v==fa) continue;
		if(vis[v]) {
			r=-1;
			return;
		}
		if(G[v].size()==1) {
			vis[v]=1;
			cnt++;
		} else {
			if(++bcnt>=(fa==0 ? 3 : 2)) {
				r=-1;
				return;
			}
			dfs(v,u);
		}
		if(r==-1) return;
	}
	if(fa==0&&bcnt!=0) r=(r*2)%p;
	r=(r*fact[cnt])%p;
}

int main()
{
	ios::sync_with_stdio(false);

	int n,m;
	cin>>n>>m>>p;

	if(m>=n) {
		cout<<"0"<<endl;
		return 0;
	}

	for(int i=0;i<m;i++) {
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	fact[0]=1;
	for(int i=1;i<=n;i++) {
		fact[i]=(fact[i-1]*i)%p;
	}

	long long ans=1;
	int tcnt=0,scnt=0;
	for(int i=1;i<=n;i++) {
		if(!vis[i]&&G[i].size()>1) {
			r=2;
			dfs(i);
			if(r==-1) {
				cout<<"0"<<endl;
				return 0;
			}
			ans=(ans*r)%p;
			tcnt++;
		} else if(!vis[i]&&G[i].size()==1&&G[G[i][0]].size()==1) {
			vis[i]=vis[G[i][0]]=1;
			ans=(ans*2)%p;
			tcnt++;
		} else if(G[i].size()==0) {
			scnt++;
		}
	}

	for(int i=n-scnt+2;i<n+2;i++) {
		ans=(ans*i)%p;
	}

	cout<<ans*fact[tcnt]%p<<endl;
	return 0;
}