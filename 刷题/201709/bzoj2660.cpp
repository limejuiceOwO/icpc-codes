//最多的方案 斐波那契数+dp计数+找规律？
#include <iostream>
#include <algorithm>
#define N 90
using namespace std;

long long fib[N],dp[N][2];//0不拆，1拆
int pos[N],fcnt,pcnt;

int main()
{
	long long n;
	cin>>n;

	fib[1]=1;fib[2]=2;
	for(fcnt=3;fib[fcnt-1]<n;fcnt++) {
		fib[fcnt]=fib[fcnt-1]+fib[fcnt-2];
	}

	for(int i=fcnt-1;i>0;i--) {
		if(n>=fib[i]) {
			pos[pcnt++]=i;
			n-=fib[i];
		}
	}

	pos[pcnt]=0;
	dp[pcnt][0]=1;
	for(int i=pcnt-1;i>=0;i--) {
		dp[i][0]=dp[i+1][0]+dp[i+1][1];//如果分拆fib[i]，则必须保留fib[i-1],fib[i-3],fib[i-5]......fib[2*k-1]和fib[2*k]，即f[i]=f[i-2]+1
		dp[i][1]=(pos[i]-pos[i+1]-1)/2*dp[i+1][0]+(pos[i]-pos[i+1])/2*dp[i+1][1];//每一项分拆得到的（连续）数列末尾一定不会超过pos[i+1](不拆i+1) or pos[i+1]-1(拆i+1)，否则必定重合
	}

	cout<<dp[0][0]+dp[0][1]<<endl;
	return 0;
}