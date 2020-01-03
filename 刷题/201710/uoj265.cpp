//NOIP2016 愤怒的小鸟 状压dp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 22
#define EPS 1e-10 //uoj卡eps精度什么鬼......
using namespace std;

int dp[2][(1<<19)+5],msk[N*N];
double px[N],py[N];

int main()
{
	ios::sync_with_stdio(false);

	int t,n,m;
	cin>>t;
	while(t--) {
		cin>>n>>m;
		for(int i=0;i<n;i++) {
			cin>>px[i]>>py[i];
		}

		int mcnt=0;
		for(int i=0;i<n;i++) {
			msk[mcnt++]=(1<<i);
			for(int j=i+1;j<n;j++) {
				double a,b,d;
				d=px[i]/px[j];
				a=(py[i]-py[j]*d)/(px[i]*px[i]-px[j]*px[j]*d);
				d*=d;
				b=(py[i]-py[j]*d)/(px[i]-px[j]*d);

				if(a>-EPS) continue;
				msk[mcnt]=0;//注意一定要先清空！！！
				for(int k=0;k<n;k++) {
					if(fabs(a*px[k]*px[k]+b*px[k]-py[k])<EPS) {
						msk[mcnt]|=(1<<k);
					}
				}
				mcnt++;
			}
		}

		sort(msk,msk+mcnt);
		mcnt=unique(msk,msk+mcnt)-msk;

		memset(dp[0],0x7f,sizeof(dp[0]));
		dp[0][0]=0;
		for(int i=0;i<mcnt;i++) {
			int cur=i&1;
			memcpy(dp[cur^1],dp[cur],sizeof(dp[0]));
			for(int s=0;s<(1<<n);s++) {
				dp[cur^1][s|msk[i]]=min(dp[cur^1][s|msk[i]],dp[cur][s]+1);
			}
		}

		cout<<dp[mcnt&1][(1<<n)-1]<<endl;
	}

	return 0;
}