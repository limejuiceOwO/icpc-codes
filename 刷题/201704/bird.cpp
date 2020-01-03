//MOIP2014 飞扬的小鸟 脑残背包dp 大坑
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
		id[pos[i]]=i;//?
	}
	int cur=0;
	for(int i=0;i<=n;i++) {
		int next=cur^1;
		bool ok=false;
		memset(dp[next],0x7f,sizeof(dp[next]));
		memset(dp2[next],0x7f,sizeof(dp2[next]));
		for(int j=1;i>0&&j<=m;j++) { //注意多次上升时要完整扫一遍1～m，因为单次上升到达的点可能不在L[n]～H[n]范围内
			int zz=min(j+X[i-1],m);
			dp[cur][zz]=min(dp[cur][zz],dp[cur][j]+1);
		}
		for(int j=L[i]+1;j<H[i];j++) {
			if(dp[cur][j]>=INF&&dp2[cur][j]>=INF) continue;
			ok=true;
			int zz=min(j+X[i],m);//转移时不要判边界
			dp[next][zz]=min(dp[next][zz],dp[cur][j]+1);
			dp[next][zz]=min(dp[next][zz],dp2[cur][j]+1);
			zz=j-Y[i];
			if(zz>0) {
				dp2[next][zz]=min(dp2[next][zz],dp[cur][j]);
				dp2[next][zz]=min(dp2[next][zz],dp2[cur][j]);
			}
		}
		if(!ok) {
			cout<<"0"<<endl;
			cout<<id[i]<<endl;
			return 0;
		}
		cur=next;
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