#include <cstdio>
#include <algorithm>
#include <vector>
#define N 400005
using namespace std;

int rt[N],qur[N],ans[N];
char mark[N];
vector<int> G[N];

int getrt(int u)
{
	return rt[u]==u ? u : (rt[u]=getrt(rt[u]));
}

int merge(int a,int b)
{
	int ra=getrt(a),rb=getrt(b);
	if(ra==rb) return 0;
	rt[ra]=rb;
	return 1;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) {
		rt[i]=i;
	}
	for(int i=0;i<m;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int k,cnt=0;
	scanf("%d",&k);
	for(int i=0;i<k;i++) {
		scanf("%d",&qur[i]);
		mark[qur[i]]=1;
	}
	for(int i=0;i<n;i++) {
		if(!mark[i]) {
			cnt++;
			for(unsigned int j=0;j<G[i].size();j++) {
				if(!mark[G[i][j]])
					cnt-=merge(i,G[i][j]);
			}
		}
	}
	ans[k]=cnt;

	for(int i=k-1;i>=0;i--) {
		cnt++;
		for(unsigned int j=0;j<G[qur[i]].size();j++) {
			int v=G[qur[i]][j];
			if(mark[v]) continue;
			cnt-=merge(qur[i],v);
		}
		mark[qur[i]]=0;
		ans[i]=cnt;
	}

	for(int i=0;i<=k;i++)
		printf("%d\n",ans[i]);

	return 0;
}