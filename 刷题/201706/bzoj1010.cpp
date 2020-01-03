#include <iostream>
#include <algorithm>
#define N 50005
#define EPS 1e-7
using namespace std;

long long sum[N],dp[N];
int que[N],head,tail;
int L;

long long sq(long long x)
{
	return x*x;
}

double k(int p,int q)
{
	return ((double)dp[p]+sq(sum[p])-dp[q]-sq(sum[q]))/(sum[p]-sum[q]);
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n>>L;

	for(int i=1;i<=n;i++) {
		cin>>sum[i];
		sum[i]+=sum[i-1]+1;
	}

	tail=1;
	for(int i=1;i<=n;i++) {
		while(tail-head>1&&k(que[head+1],que[head])-2*(sum[i]-L-1)<EPS) head++; //sum[i]单调递增，所以队头比2*(sum[i]-L-1)小的点不会再比它大
		dp[i]=dp[que[head]]+sq(sum[i]-sum[que[head]]-L-1); //mdzz:注意先更新dp再取i的斜率……
		while(tail-head>1&&k(i,que[tail-1])-k(que[tail-1],que[tail-2])<EPS) tail--; //整个队列单调递增，中间上凸的点不可能是最优解
		que[tail++]=i;
	}

	cout<<dp[n]<<endl;
	return 0;
}