//Cash Machine 多重背包+单调队列
#include <iostream>
#include <algorithm>
#define N 15
#define V 100005
using namespace std;

int size[N],cnt[N];
int dp[N][V];

int main()
{
	ios::sync_with_stdio(false);

	while(1) {
		int n,v;
		cin>>v>>n;
		if(cin.eof()) break;
		for(int i=1;i<=n;i++)
			cin>>cnt[i]>>size[i];

		int que[V],idx[V];
		for(int i=1;i<=n;i++) {
			for(int j=0;j<size[i];j++) {
				int head=0,tail=0;
				for(int k=j;k<=v;k+=size[i]) {
					int c=k/size[i];
					while(head<tail&&que[tail-1]<dp[i-1][k]-size[i]*c) tail--;
					idx[tail]=c;
					que[tail++]=dp[i-1][k]-size[i]*c;

					if(head<tail&&c-idx[head]>cnt[i]) head++;

					dp[i][k]=que[head]+c*size[i];
				}
			}
		}

		cout<<dp[n][v]<<endl;
	}
	return 0;
}