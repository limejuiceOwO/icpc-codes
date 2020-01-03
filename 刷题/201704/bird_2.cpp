//NOIP2014 飞扬的小鸟 脑残背包dp 递推版
#include <iostream>
#include <algorithm>
#include <cstring>
#define N 10005
#define M 1005
#define INF 100000000
using namespace std;

int L[N],H[N],X[N],Y[N],id[N],pos[N];
int dp[2][M],dp2[2][M];//dp->从上一个位置上升到达，dp2->从上一个位置下降到达
int n,m;

int main()
{
	ios::sync_with_stdio(false);
	int k;
	cin>>n>>m>>k;
	for(int i=0;i<n;i++) {
		//L[i]=0;
		H[i]=m+1;
		cin>>X[i]>>Y[i];
	}
	H[n]=H[n+1]=m+1;
	for(int i=0;i<k;i++) {
		int x,l,h;
		cin>>x>>l>>h;
		L[x]=l;
		H[x]=h;
		pos[i]=x;
	}
	sort(pos,pos+k);
	for(int i=0;i<k;i++) {
		id[pos[i]]=i;
	}
	int cur=1;
	for(int i=1;i<=n;i++) {
		int prev=cur^1;
		bool ok=false;
		memset(dp[cur],0x7f,sizeof(dp[cur]));
		memset(dp2[cur],0x7f,sizeof(dp2[cur]));
		for(int j=1;j<=m;j++) {
			int zz=j-X[i-1];
			if(zz>L[i-1]&&zz<H[i-1]) {
				dp[cur][j]=min(dp[prev][zz]+1,dp[cur][j]);
				dp[cur][j]=min(dp2[prev][zz]+1,dp[cur][j]);
			}
			zz=j+Y[i-1];
			if(zz>L[i-1]&&zz<H[i-1]) {
				dp2[cur][j]=min(dp[prev][zz],dp[prev][zz]);
				dp2[cur][j]=min(dp[prev][zz],dp2[prev][zz]);
			}
			if(j==m) {
				for(zz=max(m-X[i-1],L[i-1]+1);zz<H[i-1];zz++) {
					dp[cur][m]=min(dp[prev][zz]+1,dp[cur][m]);
					dp[cur][m]=min(dp2[prev][zz]+1,dp[cur][m]);
				}
			}
		}
		for(int j=1;j<=m;j++) {
			int zz=j-X[i-1];
			if(zz>0) dp[cur][j]=min(dp[cur][zz]+1,dp[cur][j]);
			if(j==m) {
				for(int zz=max(m-X[i-1],1);zz<=m;zz++) {
					dp[cur][m]=min(dp[cur][zz]+1,dp[cur][m]);
				}
			}
		}
		for(int j=L[i]+1;j<H[i];j++) {
			if(dp[cur][j]<INF||dp2[cur][j]<INF) ok=true;
		}
		//out
		//for(int z=1;z<=m;z++) if(dp[cur][z]>=INF&&dp2[cur][z]>=INF)  cout<<"I ";
		//else cout<<min(dp2[cur][z],dp[cur][z])<<" ";
		//cout<<endl;
		if(!ok) {
			cout<<"0"<<endl;
			cout<<id[i]<<endl;
			return 0;
		}
		cur^=1;
	}
	cur^=1;
	int ans=INF;
	for(int i=L[n]+1;i<H[n];i++) {
		ans=min(ans,dp[cur][i]);
		ans=min(ans,dp2[cur][i]);
	}
	cout<<"1"<<endl;
	cout<<ans<<endl;
	return 0;
}