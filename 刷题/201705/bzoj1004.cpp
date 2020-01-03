#include <iostream>
#include <algorithm>
#include <cstring>
#define N 25
using namespace std;

long long dp[2][N][N][N];
int tmp[N*3],round[N*3];
char vis[N*3];

long long fac(long long x,long long p)
{
	long long ans=1;
	for(long long i=2;i<=x;i++) {
		ans=(ans*i)%p;
	}
	return ans;
}

long long qpow(long long x,long long k,long long p)
{
	long long ans=1;
	while(k) {
		if(k&1) ans=(ans*x)%p;
		x=(x*x)%p;
		k>>=1;
	}
	return ans;
}

int dfs(int u)
{
	if(vis[u]) return 0;

	vis[u]=1;
	return dfs(tmp[u])+1;
}

int main()
{
	int sr,sg,sb,m,p;
	cin>>sr>>sb>>sg>>m>>p;

	long long n=sr+sg+sb;

	long long ans=fac(n,p);
	ans=(ans*qpow(fac(sr,p),p-2,p))%p;
	ans=(ans*qpow(fac(sg,p),p-2,p))%p;
	ans=(ans*qpow(fac(sb,p),p-2,p))%p;

	for(int i=0;i<m;i++) {
		int cnt=0;
		for(int j=1;j<=n;j++) cin>>tmp[j];

		memset(vis,0,sizeof(vis));
		for(int j=1;j<=n;j++) {
			int res;
			if((res=dfs(j))>0) round[cnt++]=res;
		}
		
		int cur=1;
		dp[0][0][0][0]=1;
		for(int z=0;z<cnt;z++) {
			int prev=cur^1;
			memset(dp[cur],0,sizeof(dp[0]));
			for(int i=0;i<=sr;i++) {
				for(int j=0;j<=sg;j++) {
					for(int k=0;k<=sb;k++) {
						if(i>=round[z]) dp[cur][i][j][k]=(dp[cur][i][j][k]+dp[prev][i-round[z]][j][k])%p;
						if(j>=round[z]) dp[cur][i][j][k]=(dp[cur][i][j][k]+dp[prev][i][j-round[z]][k])%p;
						if(k>=round[z]) dp[cur][i][j][k]=(dp[cur][i][j][k]+dp[prev][i][j][k-round[z]])%p;
					}
				}
			}
			cur^=1;
		}
		ans=(ans+dp[cur^1][sr][sg][sb])%p;
	}

	cout<<(ans*qpow(m+1,p-2,p))%p<<endl;
	//cout<<ans<<endl;

	return 0;
}