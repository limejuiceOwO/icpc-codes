#include <iostream>
#include <algorithm>
#define N 105
#define V 10005
using namespace std;

int size[N],cnt[N],cost[N];
int dp[N][V];

int main()
{
	int n,v;
	cin>>n>>v;
	for(int i=1;i<=n;i++)
		cin>>cnt[i]>>size[i]>>cost[i];

	int que[V],idx[V];
	for(int i=1;i<=n;i++) {
		for(int j=0;j<size[i];j++) {
			int head=0,tail=0;
			for(int k=j;k<=v;k+=size[i]) {
				int c=k/size[i];
				while(head<tail&&que[tail-1]<dp[i-1][k]-cost[i]*c) tail--;
				idx[tail]=c;
				que[tail++]=dp[i-1][k]-size[i]*c;

				if(head<tail&&c-idx[head]>cnt[i]) head++;

				dp[i][k]=que[head]+c*cost[i];
			}
		}
	}

	cout<<dp[n][v]<<endl;
	return 0;
}