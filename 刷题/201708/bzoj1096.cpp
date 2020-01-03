#include <iostream>
#include <algorithm>
#define N 1000005
using namespace std;

long long pp[N],p[N],x[N],c[N],q[N];
long long dp[N];
int que[N];

double slope(int i,int j)
{
	return ((double)dp[i]+q[i]-dp[j]-q[j])/(p[i]-p[j]);
}

int main()
{
	ios::sync_with_stdio(false);

	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>x[i]>>pp[i]>>c[i];
		p[i]=p[i-1]+pp[i];
		q[i]=q[i-1]+pp[i]*x[i];
	}

	//que[0]=dp[0]=0;
	int head=0,tail=1;
	for(int i=1;i<=n;i++) {
		while(head+1<tail&&slope(que[head],que[head+1])<x[i]) head++;
		dp[i]=dp[que[head]]+x[i]*(p[i]-p[que[head]])-(q[i]-q[que[head]])+c[i];
		while(head+1<tail&&slope(i,que[tail-1])<slope(que[tail-1],que[tail-2])) tail--;
		que[tail++]=i;
	}

	cout<<dp[n]<<endl;
	return 0;
}